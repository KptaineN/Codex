/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler-1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiefer <nkiefer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 22:35:23 by nkiefer           #+#    #+#             */
/*   Updated: 2025/08/13 23:18:14 by nkiefer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_pipe(t_shell *shell, char **argv)
{
	(void)shell;
	(void)argv;
	printf("Handling PIPE (|)\n");
	return (0);
}

int	handle_and(t_shell *shell, char **argv)
{
	(void)shell;
	(void)argv;
	printf("Handling AND (&&)\n");
	return (0);
}

int	handle_or(t_shell *shell, char **argv)
{
	(void)shell;
	(void)argv;
	printf("Handling OR (||)\n");
	return (0);
}

void	handle_error(const char *message)
{
	perror(message);
	exit(EXIT_FAILURE);
}

void	handle_echo(t_shell *shell)
{
	int	i;

	i = 0;
	if (shell->args && shell->args[1])
	{
		i = 1;
		while (shell->args[i])
		{
			printf("%s ", shell->args[i]);
			i++;
		}
		printf("\n");
	}
	else
		printf("\n");
}
