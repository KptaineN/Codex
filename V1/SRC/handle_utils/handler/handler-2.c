/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler-2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkief <nkief@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 16:25:46 by eganassi          #+#    #+#             */
/*   Updated: 2025/08/20 16:12:03 by nkief            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_cd(t_shell *shell)
{
	if (shell->args && shell->args[1])
	{
		if (chdir(shell->args[1]) != 0)
			perror("cd");
	}
	else
		ft_putendl_fd("cd: missing argument", STDERR_FILENO);
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
		ft_putendl_fd("No environment variables set.", STDERR_FILENO);
}

void	handle_export(t_shell *shell)
{
	if (shell->args && shell->args[1])
		printf("Exporting: %s\n", shell->args[1]);
	else
		ft_putendl_fd("export: missing argument", STDERR_FILENO);
}

void	handle_unset(t_shell *shell)
{
	if (shell->args && shell->args[1])
		printf("Unsetting: %s\n", shell->args[1]);
	else
		ft_putendl_fd("unset: missing argument", STDERR_FILENO);
}
