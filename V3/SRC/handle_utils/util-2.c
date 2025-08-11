/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util-2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiefer <nkiefer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 16:30:45 by eganassi          #+#    #+#             */
/*   Updated: 2025/06/17 14:23:50 by nkiefer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	handle_echo(t_shell *shell)
{
	// Handle the 'echo' command
	if (shell->args && shell->args[1])
	{
		for (int i = 1; shell->args[i]; i++)
		{
			printf("%s ", shell->args[i]);
		}
		printf("\n");
	}
	else
	{
		printf("\n"); // Just print a newline if no arguments
	}
}
/*
void	handle_pipes(t_shell *shell)
{
	// Handle pipes in the command
	// This is a placeholder function; you would implement actual pipe handling here
	printf("Handling pipes...\n");
}

void	handle_redirection(t_shell *shell)
{
	// Handle redirection in the command
	// This is a placeholder function; you would implement actual redirection handling here
	printf("Handling redirection...\n");
}*/

void	handle_builtin(t_shell *shell)
{
	// Handle built-in commands like cd, exit, env, export, unset, echo
	if (ft_strncmp(shell->args[0], "cd", ft_strlen("cd") + 1) == 0)
		handle_cd(shell);
	else if (ft_strncmp(shell->args[0], "exit", ft_strlen("exit") + 1) == 0)
		handle_exit(shell);
	else if (ft_strncmp(shell->args[0], "env", ft_strlen("env") + 1) == 0)
		handle_env(shell);
	else if (ft_strncmp(shell->args[0], "export", ft_strlen("export") + 1) == 0)
		handle_export(shell);
	else if (ft_strncmp(shell->args[0], "unset", ft_strlen("unset") + 1) == 0)
		handle_unset(shell);
	else if (ft_strncmp(shell->args[0], "echo", ft_strlen("echo") + 1) == 0)
		handle_echo(shell);
	else
		fprintf(stderr, "%s: command not found\n", shell->args[0]);
}
/*
void	handle_external(t_shell *shell)
{
	// Handle external commands (not built-in)
	// This is a placeholder function; you would implement actual command execution here
	printf("Handling external command: %s\n", shell->args[0]);
	// You would typically use execvp or similar functions to execute the command
}*/
