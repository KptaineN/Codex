



#include "../../include/minishell.h"

static void unset_one(t_list **env, const char *key)
{
    t_list *prev = NULL;
    t_list *cur = *env;

    while (cur)
    {
        t_env *env_var = cur->content;
        if (ft_strcmp(env_var->key, key) == 0)
        {
            if (prev)
                prev->next = cur->next;
            else
                *env = cur->next;
            free(env_var->key);
            free(env_var->value);
            free(env_var);
            free(cur);
            return;
        }
        prev = cur;
        cur = cur->next;
    }
}

int builtin_unset(t_shell *shell, char **argv)
{
    // argv[0] == "unset"
    int i = 1;
    while (argv[i])
    {
        unset_one((t_list **)&shell->env, argv[i]);
        i++;
    }
    shell->exit_status = 0;
    return 0;
}
void unset_env_value(t_list **env, const char *key)
{
    t_list *tmp = *env;
    t_list *prev = NULL;

    while (tmp)
    {
        t_env *env_var = tmp->content;
        if (ft_strcmp(env_var->key, key) == 0)
        {
            if (prev)
                prev->next = tmp->next;
            else
                *env = tmp->next;
            free(env_var->key);
            free(env_var->value);
            free(env_var);
            free(tmp);
            return;
        }
        prev = tmp;
        tmp = tmp->next;
    }
}




