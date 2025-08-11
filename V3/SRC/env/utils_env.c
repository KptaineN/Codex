#include "../../include/minishell.h"

char    **list_to_envp(t_list *env)
{
    t_list  *it;
    char    **envp;
    int     count;
    int     i;

    count = 0;
    it = env;
    while (it)
    {
        if (ft_strchr((char *)it->content, '='))
            count++;
        it = it->next;
    }
    envp = malloc(sizeof(char *) * (count + 1));
    if (!envp)
        return (NULL);
    i = 0;
    it = env;
    while (it)
    {
        if (ft_strchr((char *)it->content, '='))
        {
            envp[i] = ft_strdup((char *)it->content);
            if (!envp[i])
            {
                while (i-- > 0)
                    free(envp[i]);
                free(envp);
                return (NULL);
            }
            i++;
        }
        it = it->next;
    }
    envp[i] = NULL;
    return (envp);
}

