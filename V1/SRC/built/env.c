/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiefer <nkiefer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 00:00:00 by chatgpt           #+#    #+#             */
/*   Updated: 2025/08/18 00:00:00 by chatgpt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int builtin_env(t_shell *shell, char **args)
{
    t_list  *cur;
    t_env   *env;

    (void)args;
    cur = shell->env;
    while (cur)
    {
        env = cur->content;
        if (env->value)
        {
            write(STDOUT_FILENO, env->key, ft_strlen(env->key));
            write(STDOUT_FILENO, "=", 1);
            write(STDOUT_FILENO, env->value, ft_strlen(env->value));
            write(STDOUT_FILENO, "\n", 1);
        }
        cur = cur->next;
    }
    shell->exit_status = 0;
    return (0);
}
