/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiefer <nkiefer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 15:27:31 by nkiefer           #+#    #+#             */
/*   Updated: 2025/08/13 19:58:06 by nkiefer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_env(t_shell *shell, char **args)
{
	t_list	*cur;
	t_env	*env;

	if (args[1])
	{
		ft_putstr_fd("( ͡ಠ ʖ̯ ͡ಠ)╭∩╮minishell: env: too many arguments\n", 2);
		return (shell->exit_status = 1);
	}
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
