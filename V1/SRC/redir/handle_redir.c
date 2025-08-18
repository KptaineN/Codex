/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ChatGPT <chatgpt@example.com>               +#+  +:+      
	+#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 00:00:00 by ChatGPT           #+#    #+#             */
/*   Updated: 2025/10/15 00:00:00 by ChatGPT          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	open_infile(t_shell *shell, const char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		perror(path);
		return (1);
	}
	if (shell->fd_in != STDIN_FILENO && shell->fd_in != -1)
		close(shell->fd_in);
	shell->fd_in = fd;
	return (0);
}

static int	open_outfile(t_shell *shell, const char *path, int flags)
{
	int	fd;

	fd = open(path, flags, 0644);
	if (fd < 0)
	{
		perror(path);
		return (1);
	}
	if (shell->fd_out != STDOUT_FILENO && shell->fd_out != -1)
		close(shell->fd_out);
	shell->fd_out = fd;
	return (0);
}

int	handle_redirect_in(t_shell *shell, char **argv)
{
	if (!argv || !argv[1])
	{
		ft_putendl_fd("minishell: syntax error near unexpected token `newline'",
			STDERR_FILENO);
		return (1);
	}
	return (open_infile(shell, argv[1]));
}

int	handle_redirect_out(t_shell *shell, char **argv)
{
	if (!argv || !argv[1])
	{
		ft_putendl_fd("minishell: syntax error near unexpected token `newline'",
			STDERR_FILENO);
		return (1);
	}
	return (open_outfile(shell, argv[1], O_CREAT | O_TRUNC | O_WRONLY));
}

int	handle_append(t_shell *shell, char **argv)
{
	if (!argv || !argv[1])
	{
		ft_putendl_fd("minishell: syntax error near unexpected token `newline'",
			STDERR_FILENO);
		return (1);
	}
	return (open_outfile(shell, argv[1], O_CREAT | O_APPEND | O_WRONLY));
}
