
#include "echo.h"
static int	is_echo_n_flag(const char *s)
{
    int	i = 0;

    if (!s || s[0] != '-')
        return (0);
    i = 1;
    while (s[i])
    {
        if (s[i] != 'n')
            return (0);
        i++;
    }
    return (s[1] != '\0');
}

int	builtin_echo(t_shell *shell, char **argv)
{
    int	i = 0;
    int	newline = 0;

    i = 1;
    newline = 1;
    while (argv[i] && is_echo_n_flag(argv[i]))
    {
        newline = 0;
        i++;
    }
    while (argv[i])
    {
        ft_putstr_fd(argv[i], STDOUT_FILENO);
        if (argv[i + 1])
            ft_putchar_fd(' ', STDOUT_FILENO);
        i++;
    }
    if (newline)
        ft_putchar_fd('\n', STDOUT_FILENO);
    (void)shell;
    return (0);
}

//#include "../../include/minishell.h"

/*** Helpers pour env ***/


/*** Gestion $...
// remplace $?, $VAR, touche perso $N
// récupère la valeur associée à $…


// Renvoie une chaîne allouée pour les variables “spéciales”
//- si key == "NOE"    → la touche perso
 // - si key == "ENRICO" → on ne fait rien (on renvoie NULL)
 // - sinon             → NULL

static char *get_special_var(const char *key)
{
    if (ft_strncmp(key, "NRICO", ft_strlen("NRICO") + 1) == 0)
        return ft_strdup("le 2 eme meilleur dev de la galaxie 🚀");;
    if (ft_strncmp(key, "NOE", ft_strlen("NOE") + 1) == 0)
        return ft_strdup("le meilleur dev de la galaxie 🚀");
    return NULL;
}

//Récupère la valeur après $…
//
static char *get_dollar_value(const char *arg, int *pos, t_shell *sh)
{
    int  k = *pos + 1;
    char *key;
    char *val_env;
    char *val;

    if (arg[k] == '?')
    {
        val = ft_itoa(sh->exit_status);
        *pos = k + 1;
        return val;
    }

    //on lit l’identifiant [A-Za-z0-9_]
    int len = 0;
    while (ft_isalnum(arg[k + len]) || arg[k + len] == '_')
        len++;
    if (len == 0)
    {
         // clé vide → on ne touche pas à res, on avance d’1
        *pos = k;
        return NULL;
    }
    key = ft_substr(arg, k, len);

    // d’abord dans l’env
    val_env = find_env_value(sh->env, key);
    if (val_env)
        val = ft_strdup(val_env);
    / sinon, test “spécial”
    else
        val = get_special_var(key);

    free(key);
    *pos = k + len;
    return val;
}*/

/*
    int len = 0;
    while (ft_isalnum(arg[k + len]) || arg[k + len] == '_')
        len++;
    if (len == 0)
    {
        *pos = k;
        return NULL;
    }
    key = ft_substr(arg, k, len);
    val_env = find_env_value(sh->env, key);
    if (val_env)
        val = ft_strdup(val_env);
    else
        val = get_special_var(key);
    free(key);
    *pos = k + len;
    return val;
*/





/*
static void print_echo_args(char **args, int start, t_shell *sh)
{
    bool first = true;

    for (int i = start; args[i]; i++)
    {
        if (!first)
            write(1, " ", 1);
        first = false;

        char *tmp = replace_variables(args[i], sh);
        char *out = remove_quotes(tmp);
        free(tmp);

        write(1, out, ft_strlen(out));
        free(out);
    }
}
*/
/*
int builtin_echo(t_shell *sh, t_token *token)
{
    t_subtoken_conainter *args = token->u.cmd_args_parts;
    int n_args = count_subtoken_args(args);
    bool no_nl = false;
    bool first = true;
    int i = 0;

    while (i < n_args)
    {
        size_t len = 0;
        for (int p = 0; p < args[i].n_parts; p++)
            len += args[i].parts[p].len;
        char *raw = malloc(len + 1);
        char *dst = raw;
        for (int p = 0; p < args[i].n_parts; p++)
        {
            memcpy(dst, args[i].parts[p].p, args[i].parts[p].len);
            dst += args[i].parts[p].len;
        }
        *dst = '\0';

        char *tmp = replace_variables(raw, sh);
        free(raw);
        char *out = remove_quotes(tmp);
        free(tmp);

        if (!is_n_flag(out))
        {
            free(out);
            break;
        }
        no_nl = true;
        free(out);
        i++;
    }

    for (int j = i; j < n_args; j++)
    {
        size_t len = 0;
        for (int p = 0; p < args[j].n_parts; p++)
            len += args[j].parts[p].len;
        char *raw = malloc(len + 1);
        char *dst = raw;
        for (int p = 0; p < args[j].n_parts; p++)
        {
            memcpy(dst, args[j].parts[p].p, args[j].parts[p].len);
            dst += args[j].parts[p].len;
        }
        *dst = '\0';

        char *tmp = replace_variables(raw, sh);
        free(raw);
        char *out = remove_quotes(tmp);
        free(tmp);

        if (!first)
            write(1, " ", 1);
        first = false;
        write(1, out, ft_strlen(out));
        free(out);
    }

    if (!no_nl)
        write(1, "\n", 1);

    sh->exit_status = 0;
    return 0;
}*/

/*
static char *find_env_value(t_env *env, const char *key)
{
    while (env)
    {
        if (ft_strncmp(env->key, key, ft_strlen(key) + 1) == 0)
            return (env->value);
        env = env->next;
    }
    return (NULL);
}



// Gestion $...
// remplace $?, $VAR, touche perso $N
// Récupère la valeur associée à $…


// Renvoie une chaîne allouée pour les variables “spéciales”
// - si key == "NOE"    → la touche perso
 * - si key == "ENRICO" → on ne fait rien (on renvoie NULL)
 * - sinon             → NULL

static char *get_special_var(const char *key)
{
    if (ft_strncmp(key, "NRICO", ft_strlen("NRICO") + 1) == 0)
        return ft_strdup("le 2 eme meilleur dev de la galaxie 🚀");;
    if (ft_strncmp(key, "NOE", ft_strlen("NOE") + 1) == 0)
        return ft_strdup("le meilleur dev de la galaxie 🚀");
    return NULL;
}

// Récupère la valeur après $… **
static char *get_dollar_value(const char *arg, int *pos, t_shell *sh)
{
    int  k = *pos + 1;
    char *key;
    char *val_env;
    char *val;

    if (arg[k] == '?')
    {
        val = ft_itoa(sh->exit_status);
        *pos = k + 1;
        return val;
    }

    //on lit l’identifiant [A-Za-z0-9_]
    int len = 0;
    while (ft_isalnum(arg[k + len]) || arg[k + len] == '_')
        len++;
    if (len == 0)
    {
         // clé vide → on ne touche pas à res, on avance d’1
        *pos = k;
        return NULL;
    }
    key = ft_substr(arg, k, len);

    // d’abord dans l’env
    val_env = find_env_value(sh->env, key);
    if (val_env)
        val = ft_strdup(val_env);
    // sinon, test “spécial”
    else
        val = get_special_var(key);

    free(key);
    *pos = k + len;
    return val;
}

** Gestion $... *
static int handle_dollar(char *res, const char *arg, int *i, t_shell *sh)
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
}


// Fonction corrigée pour replace_variables
char *replace_variables(const char *arg, t_shell *sh)
{
    int  i = 0, j = 0;
    bool in_sq = false, in_dq = false;
    // on alloue un buffer généreux
    char *res = malloc(ft_strlen(arg) * 50 + 1);
    if (!res) return NULL;

    while (arg[i])
    {
        // ouverture/fermeture de quotes
        if (arg[i] == '\'' && !in_dq)
        {
            in_sq = !in_sq;
            res[j++] = arg[i++]; // On copie la quote
        }
        else if (arg[i] == '"' && !in_sq)
        {
            in_dq = !in_dq;
            res[j++] = arg[i++]; // On copie la quote
        }
        // cas d'un '$' hors quotes simples
        else if (arg[i] == '$' && !in_sq)
        {
            int written = handle_dollar(&res[j], arg, &i, sh);
            if (written > 0)
            {
                // on a développé une variable
                j += written;
            }
            else
            {
                // pas de variable valide → on copie le '$' tel quel
                res[j++] = arg[i++];
            }
        }
        else
        {
            // caractère normal (ou '$' dans simple quote)
            res[j++] = arg[i++];
        }
    }
    res[j] = '\0';
    return res;
}*/
char *remove_quotes(const char *arg)
{
    size_t i = 0, j = 0;
    bool in_sq = false, in_dq = false;
    char *res = malloc(ft_strlen(arg) + 1);
    if (!res)
        return NULL;

    while (arg[i])
    {
        if (arg[i] == '\'' && !in_dq)
        {
            // Cette quote simple est un délimiteur (pas dans des doubles quotes)
            in_sq = !in_sq;
            i++; // On l'ignore (délimiteur)
        }
        else if (arg[i] == '"' && !in_sq)
        {
            // Cette quote double est un délimiteur (pas dans des simples quotes)
            in_dq = !in_dq;
            i++; // On l'ignore (délimiteur)
        }
        else
        {
            // Tout autre caractère, y compris les quotes qui ne sont PAS des délimiteurs
            res[j++] = arg[i++];
        }
    }
    res[j] = '\0';
    return res;
}

/*
int builtin_echo(char **args, t_shell *sh)
{
    int  i       = 1;
    bool no_nl   = false;

    // 2) Détection stricte de -n
    while (args[i] && ft_strcmp(args[i], "-n") == 0) {
        no_nl = true;
        i++;
    }

    // 3) Affichage des arguments (expansion + suppression de quotes)
    bool first = true;
    while (args[i])
    {
        if (!first)
            write(1, " ", 1);
        first = false;
        char *tmp = replace_variables(args[i], sh);
        char *out = remove_quotes(tmp);
        free(tmp);
        write(1, out, ft_strlen(out));
        free(out);
        i++;
    }

    if (!no_nl)
        write(1, "\n", 1);

    sh->exit_status = 0;
    return 0;
}*/
