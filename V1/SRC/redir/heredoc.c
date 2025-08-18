/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiefer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 02:24:04 by nkiefer           #+#    #+#             */
/*   Updated: 2025/08/18 02:24:06 by nkiefer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redir.h"

/* 1) Parent: ignorer SIGINT/SIGQUIT pendant la création du heredoc */
static void	heredoc_parent_ignore_signals(void)
{
	struct sigaction	sa;

	sa.sa_handler = SIG_IGN;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
}

/* 2) Enfant: boucle lecture/écriture avec expansion si non quoté */
static void	heredoc_child_loop(int wfd, t_delim d, t_shell *sh)
{
	char	*line;
	char	*exp;

	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (ft_strcmp(line, d.clean) == 0)
		{
			free(line);
			break ;
		}
		if (!d.quoted)
		{
			exp = expand_vars_in_line(line, sh);
			free(line);
			line = exp;
		}
		write(wfd, line, ft_strlen(line));
		write(wfd, "\n", 1);
		free(line);
	}
}

/* 3) Enfant: config signaux, ferme lecture, exécute la boucle, _exit(0) */
static void	heredoc_child_exec(int hd[2], t_delim d, t_shell *sh)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_IGN);
	rl_catch_signals = 0;
	close(hd[0]);
	heredoc_child_loop(hd[1], d, sh);
	close(hd[1]);
	_exit(0);
}

/* 4) Parent: wait, restore signaux, renvoie -2 si Ctrl-C sinon fd lecture */
static int	heredoc_wait_and_finish(pid_t pid, int rfd)
{
	int	status;

	waitpid(pid, &status, 0);
	init_signals();
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
	{
		close(rfd);
		return (-2);
	}
	return (rfd);
}

/* 5) Fonction principale */
int	build_heredoc_fd(t_delim d, t_shell *sh)
{
	int		hd[2];
	pid_t	pid;

	heredoc_parent_ignore_signals();
	if (pipe(hd) < 0)
	{
		perror("pipe");
		init_signals();
		return (-1);
	}
	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		close(hd[0]);
		close(hd[1]);
		init_signals();
		return (-1);
	}
	if (pid == 0)
		heredoc_child_exec(hd, d, sh);
	close(hd[1]);
	return (heredoc_wait_and_finish(pid, hd[0]));
}
