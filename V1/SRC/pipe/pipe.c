/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiefer <nkiefer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 23:26:15 by nkiefer           #+#    #+#             */
/*   Updated: 2025/08/13 23:33:55 by nkiefer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipe.h"

static void	child_setup_io(int prev_fd, int pipe_fd[2])
{
	if (prev_fd != -1)
	{
		if (dup2(prev_fd, STDIN_FILENO) == -1)
			perror("dup2");
		close(prev_fd);
	}
	if (pipe_fd[1] != -1)
	{
		if (dup2(pipe_fd[1], STDOUT_FILENO) == -1)
			perror("dup2");
	}
	close_if_valid(pipe_fd[0]);
	close_if_valid(pipe_fd[1]);
}

static pid_t	fork_and_run(t_shell *sh, t_token *tok, int prev_fd,
		int pipe_fd[2])
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		return (-1);
	}
	if (pid == 0)
	{
		child_setup_io(prev_fd, pipe_fd);
		execute_cmd(sh, tok);
		exit(EXIT_FAILURE);
	}
	return (pid);
}

static void	parent_after_fork(int *prev_fd, int pipe_fd[2], int has_next)
{
	close_if_valid(*prev_fd);
	if (has_next)
	{
		close_if_valid(pipe_fd[1]);
		*prev_fd = pipe_fd[0];
	}
	else
		*prev_fd = -1;
}

static int	run_stage(t_shell *sh, t_list *node, int *prev_fd, int idx)
{
	int		pipe_fd[2];
	int		has_next;
	pid_t	pid;

	has_next = (node->next != NULL);
	if (open_pipe_if_needed(has_next, pipe_fd) < 0)
		return (-1);
	pid = fork_and_run(sh, (t_token *)node->content, *prev_fd, pipe_fd);
	if (pid < 0)
	{
		close_if_valid(pipe_fd[0]);
		close_if_valid(pipe_fd[1]);
		return (-1);
	}
	sh->pids[idx] = pid;
	parent_after_fork(prev_fd, pipe_fd, has_next);
	return (0);
}

void	execute_pipeline(t_shell *sh)
{
	t_list	*curr;
	int		prev_fd;
	int		i;

	curr = sh->cmd_head;
	prev_fd = -1;
	i = 0;
	while (curr)
	{
		if (run_stage(sh, curr, &prev_fd, i) < 0)
			break ;
		curr = curr->next;
		i++;
	}
	wait_pipeline(sh, i);
}

/*
 * Execute a pipeline of commands stored in shell->cmd_head.
 * For each command we fork, redirect using dup2 and close
 * unused descriptors in both parent and child processes.
*/
