#include "../../include/minishell.h"
#include <stdlib.h>

int env_len(t_list *env)
{
    int count;

    count = 0;
    while (env)
    {
        count++;
        env = env->next;
    }
    return (count);
}

char    **list_to_envp(t_list *env)
{
    int     count;
    int     i;
    char    **envp;
    t_env   *cur;
    int     klen;
    int     vlen;

    count = 0;
    for (t_list *it = env; it; it = it->next)
        if (((t_env *)it->content)->value)
            count++;
    envp = malloc(sizeof(char *) * (count + 1));
    if (!envp)
        return (NULL);
    i = 0;
    while (env)
    {
        cur = env->content;
        if (cur->value)
        {
            klen = ft_strlen(cur->key);
            vlen = ft_strlen(cur->value);
            envp[i] = malloc(klen + 1 + vlen + 1);
            if (!envp[i])
            {
                while (i > 0)
                    free(envp[--i]);
                free(envp);
                return (NULL);
            }
            ft_strcpy(envp[i], cur->key);
            envp[i][klen] = '=';
            ft_strcpy(envp[i] + klen + 1, cur->value);
            i++;
        }
        env = env->next;
    }
    envp[i] = NULL;
    return (envp);
}

void print_env(t_list *env)
{
    while (env)
    {
        t_env *cur = env->content;
        if (cur->value)
            printf("%s=%s\n", cur->key, cur->value);
        else
            printf("%s=\n", cur->key);
        env = env->next;
    }
}

t_list *init_env(char **envp)
{
    t_list *head = NULL;
    t_list *tail = NULL;
    int     i = 0;

    while (envp[i])
    {
        char *eq = ft_strchr(envp[i], '=');
        t_env *env;
        t_list *node;

        if (!eq)
        {
            i++;
            continue;
        }
        env = malloc(sizeof(t_env));
        if (!env)
            return NULL;
        env->key = ft_substr(envp[i], 0, eq - envp[i]);
        env->value = ft_strdup(eq + 1);
        node = malloc(sizeof(t_list));
        if (!node || !env->key || !env->value)
        {
            free(env->key);
            free(env->value);
            free(env);
            free(node);
            return NULL;
        }
        node->content = env;
        node->next = NULL;
        if (!head)
            head = node;
        else
            tail->next = node;
        tail = node;
        i++;
    }
    return head;
}
