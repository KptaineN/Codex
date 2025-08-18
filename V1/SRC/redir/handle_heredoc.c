/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiefer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 02:24:13 by nkiefer           #+#    #+#             */
/*   Updated: 2025/08/18 02:24:16 by nkiefer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redir.h"

/* 1) vérifie le délimiteur et ouvre le pipe */
static int	prepare_heredoc_pipe(char **argv, int fd[2])
{
	if (!argv || !argv[1])
	{
		ft_putendl_fd("minishell: syntax error near unexpected token `newline'",
			STDERR_FILENO);
		return (0);
	}
	if (pipe(fd) == -1)
	{
		perror("pipe");
		return (0);
	}
	return (1);
}

/* 2) écrit la ligne + '\n' dans le pipe d'écriture */
static void	write_line_nl(int wfd, const char *line)
{
	write(wfd, line, ft_strlen(line));
	write(wfd, "\n", 1);
}

/* 3) boucle de lecture jusqu'au délimiteur ou EOF */
static void	heredoc_read_write(int wfd, const char *delim)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (ft_strcmp(line, delim) == 0)
		{
			free(line);
			break ;
		}
		write_line_nl(wfd, line);
		free(line);
	}
}

/* 4) remplace fd_in proprement */
static void	replace_stdin_fd(t_shell *shell, int new_fd)
{
	if (shell->fd_in != STDIN_FILENO && shell->fd_in != -1)
		close(shell->fd_in);
	shell->fd_in = new_fd;
}

/* 5) fonction principale */
int	handle_heredoc(t_shell *shell, char **argv)
{
	int	fd[2];

	if (!prepare_heredoc_pipe(argv, fd))
		return (1);
	heredoc_read_write(fd[1], argv[1]);
	close(fd[1]);
	replace_stdin_fd(shell, fd[0]);
	return (0);
}
