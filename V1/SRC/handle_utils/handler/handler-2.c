/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util-1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiefer <nkiefer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 16:25:46 by eganassi          #+#    #+#             */
/*   Updated: 2025/08/13 16:14:29 by nkiefer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_cd(t_shell *shell)
{
	if (shell->args && shell->args[1])
	{
		if (chdir(shell->args[1]) != 0)
		{
			perror("cd");
		}
	}
	else
	{
		fprintf(stderr, "cd: missing argument\n");
	}
}

void	handle_exit(t_shell *shell)
{
	int	status;

	if (shell->args && shell->args[1])
	{
		status = atoi(shell->args[1]);
		free_minishell(shell);
		exit(status);
	}
	else
	{
		free_minishell(shell);
		exit(shell->exit_status);
	}
}

void	handle_env(t_shell *shell)
{
	if (shell->env)
		print_env((t_list *)shell->env);
	else
		fprintf(stderr, "No environment variables set.\n");
}

void	handle_export(t_shell *shell)
{
	if (shell->args && shell->args[1])
		printf("Exporting: %s\n", shell->args[1]);
	else
		fprintf(stderr, "export: missing argument\n");
}

void	handle_unset(t_shell *shell)
{
	if (shell->args && shell->args[1])
		printf("Unsetting: %s\n", shell->args[1]);
	else
		fprintf(stderr, "unset: missing argument\n");
}
