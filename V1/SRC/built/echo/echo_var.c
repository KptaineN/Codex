

#include "echo.h"


/*static int handle_dollar(char *res, const char *arg, int *i, t_shell *sh)
{
    char *val;
    int  nb = 0;

    val = get_dollar_value(arg, i, sh);
    if (val)
    {
        ft_strcpy(res, val);
        nb = ft_strlen(val);
        free(val);
    }
    return nb;
}*/
// 2) handle_dollar: inchangé, mais il ne doit JAMAIS déclencher de fallback
static int handle_dollar(char *res, const char *arg, int *i, t_shell *sh)
{
    char *val = get_dollar_value(arg, i, sh); // avance *i au bon endroit
    if (!val) {
        // On ne fait rien, expansion vide ou erreur -> 0 écrit
        // (mais on ne retouche PAS *i ici)
        return 0;
    }
    int nb = ft_strlen(val);
    if (nb)
        ft_memcpy(res, val, nb);
    free(val);
    return nb;
}


static void toggle_quotes(char c, bool *in_sq, bool *in_dq)
{
    if (c == '\'' && !(*in_dq))
        *in_sq = !(*in_sq);
    else if (c == '"' && !(*in_sq))
        *in_dq = !(*in_dq);
}

/*static int process_dollar(char *dst, const char *arg, int *i, t_shell *sh)
{
    int written = handle_dollar(dst, arg, i, sh);
    if (written > 0)
        return written;
    dst[0] = arg[(*i)++];
    return 1;
}*/
// 1) process_dollar: décider le littéral avant d’appeler handle_dollar
static int process_dollar(char *dst, const char *arg, int *i, t_shell *sh)
{
    int  k = *i + 1;
    char c = arg[k];

    // "$" en fin de chaîne -> littéral
    if (c == '\0') {
        dst[0] = '$';
        (*i)++;                  // on ne consomme que '$'
        return 1;
    }
    // "$?" -> code de sortie
    if (c == '?') {
        char *s = ft_itoa(sh->exit_status);
        int   n = ft_strlen(s);
        ft_memcpy(dst, s, n);
        free(s);
        *i = k + 1;              // on a consommé "$?"
        return n;
    }
    // si le 1er char après '$' n'est pas valide pour une clé -> littéral '$'
    if (!is_valid_key_char((unsigned char)c)) {
        dst[0] = '$';
        (*i)++;                  // on ne consomme que '$'
        return 1;
    }

    // clé valide -> déléguer (peut renvoyer 0 si var inconnue)
    // ATTENTION: handle_dollar / get_dollar_value avancent *i pour nous.
    return handle_dollar(dst, arg, i, sh);
}


char *replace_variables(const char *arg, t_shell *sh)
{
    int  i = 0, j = 0;
    bool in_sq = false, in_dq = false;
    char *res = malloc(ft_strlen(arg) * 50 + 1);
    if (!res) return NULL;

    while (arg[i])
    {
        toggle_quotes(arg[i], &in_sq, &in_dq);

        if (arg[i] == '$' && !in_sq)
            j += process_dollar(&res[j], arg, &i, sh);
        else
            res[j++] = arg[i++];
    }

    res[j] = '\0';
    return res;
}
