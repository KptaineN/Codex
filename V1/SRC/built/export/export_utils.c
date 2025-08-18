/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiefer <nkiefer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 15:56:01 by nkiefer           #+#    #+#             */
/*   Updated: 2025/08/13 22:00:53 by nkiefer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "export.h"

static size_t  env_count(t_shell *shell)
{
        size_t  count;
        t_list  *current;

        count = 0;
        current = shell->env;
        while (current)
        {
                count++;
                current = current->next;
        }
        return (count);
}

static char    *create_env_entry(t_env *env)
{
        size_t  klen;
        size_t  vlen;
        char    *entry;

        klen = ft_strlen(env->key);
        if (env->value)
                vlen = ft_strlen(env->value);
        else
                vlen = 0;
        entry = malloc(klen + vlen + 2);
        if (!entry)
                return (NULL);
        ft_strcpy(entry, env->key);
        entry[klen] = '=';
        if (env->value)
                ft_strcpy(entry + klen + 1, env->value);
        else
                entry[klen + 1] = '\0';
        return (entry);
}

char    **env_to_array(t_shell *shell)
{
        size_t  n;
        char    **arr;
        size_t  i;
        t_env   *env;
        t_list  *node;

        n = env_count(shell);
        arr = malloc((n + 1) * sizeof(char *));
        if (!arr)
                return (NULL);
        i = 0;
        node = shell->env;
        while (node)
        {
                env = (t_env *)node->content;
               arr[i] = create_env_entry(env);
               if (!arr[i])
                       return (free_str_array(arr), NULL);
               i++;
               node = node->next;
       }
        arr[i] = NULL;
        return (arr);
}

void    print_export_arr(char **arr)
{
        char    *eq;
        size_t  i;

        i = 0;
        while (arr[i])
        {
                eq = ft_strchr(arr[i], '=');
                if (!eq)
                        printf("༼⌐ ■ل͟■ ༽_/¯ %s\n", arr[i]);
                else
                {
                        *eq = '\0';
                        printf(" (ಠ_ಠ)=ε/̵͇̿̿/'̿'̿-%s=\"%s\"\n", arr[i], eq + 1);
                        *eq = '=';
                }
                i++;
        }
}


