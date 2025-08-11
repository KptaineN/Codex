



#include "../../include/minishell.h"

static void unset_one(t_list **env, const char *key)
{
    t_list *prev = NULL, *cur = *env;
    while (cur)
    {
        char *equal = strchr((char*)cur->content, '=');
        if (equal)
        {
            size_t key_len = strlen(key);
            if ((size_t)(equal - (char*)cur->content) == key_len && !strncmp((char*)cur->content, key, key_len))
            {
                if (prev) prev->next = cur->next;
                else      *env = cur->next;
                free(cur->content);
                free(cur);
                return;
            }
        }
        prev = cur;
        cur  = cur->next;
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
    t_list *tmp = *env, *prev = NULL;
    size_t key_len = ft_strlen(key);

    while (tmp)
    {
        char *content = (char*)tmp->content;
        char *equal = ft_strchr(content, '=');
        if (equal && (size_t)(equal - content) == key_len && !ft_strncmp(content, key, key_len))
        {
            if (prev)
                prev->next = tmp->next;
            else
                *env = tmp->next;
            free(tmp->content);
            free(tmp);
            return;
        }
        prev = tmp;
        tmp = tmp->next;
    }
}




