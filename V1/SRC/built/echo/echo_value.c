
#include "echo.h"
/**
static char *find_env_value(t_list *env_list, const char *key)
{
    t_list *node = env_list;
    while (node)
    {
        t_list *current = (t_list *)node->content;
        if (ft_strncmp(current->key, key, ft_strlen(key) + 1) == 0)
            return current->value;
        node = node->next;
    }
    return NULL;
}*/
char *find_env_value(t_list *env, const char *key)
{
    while (env)
    {
        t_env *entry = env->content;
        if (ft_strcmp(entry->key, key) == 0)
            return entry->value;
        env = env->next;
    }
    return NULL;
}


static char *get_special_var(const char *key)
{
    if (ft_strncmp(key, "NRICO", ft_strlen("NRICO") + 1) == 0)
        return ft_strdup("le 2 eme meilleur dev de la galaxie 🚀");;
    if (ft_strncmp(key, "NOE", ft_strlen("NOE") + 1) == 0)
        return ft_strdup("le meilleur dev de la galaxie 🚀");
    return NULL;
}

int is_valid_key_char(char c)
{
    return (ft_isalnum(c) || c == '_');
}

static char *extract_key(const char *arg, int start, int *len)
{
    int i = 0;
    while (is_valid_key_char(arg[start + i]))
        i++;
    *len = i;
    if (i == 0)
        return NULL;
    return ft_substr(arg, start, i);
}

static char *get_env_or_special_value(t_shell *shell, const char *key)
{
    const char *val_env = find_env_value(shell->env, key);
    if (val_env)
        return ft_strdup(val_env);

    // spéciaux custom + "?": get_special_var doit ALLOUER si trouvé, sinon NULL
    char *sp = get_special_var(key);
    if (sp)
        return sp;

    // inconnu -> expansion vide (bash-like)
    return ft_strdup("");;
}

/*** Récupère la valeur après $… ***/
char *get_dollar_value(const char *arg, int *pos, t_shell *sh)
{
    int  k = *pos + 1;
    char *key;
    char *val;
    int len;

    if (arg[k] == '?')
    {
        val = ft_itoa(sh->exit_status);
        *pos = k + 1;
        return val;
    }
    key = extract_key(arg, k, &len);
    if (!key)
    {
        //*pos = k;
        return NULL;
    }
    val = get_env_or_special_value(sh, key);
    free(key);
    *pos = k + len;
    return val;
}
