/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiefer <nkiefer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 13:56:01 by eganassi          #+#    #+#             */
/*   Updated: 2025/08/16 16:15:25 by nkiefer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "launcher.h"

int	run_single_builtin_if_alone(t_shell *sh)
{
	t_list	*curr;
	char	**args;
	int		idx;
	int		(*handler)(t_shell *, char **);

	if (sh->n_cmd != 1)
		return (0);
	curr = sh->cmd_head;
	args = expand_cmd((t_token *)curr->content, sh->env);
	if (!args)
		return (0);
	idx = is_in_t_arr_str(sh->bcmd, args[0]);
	if (idx == -1)
	{
		free_tab(args);
		return (0);
	}
	handler = get_builtin_handler(sh->bcmd, idx);
	if (handler)
		sh->exit_status = handler(sh, args);
	free_tab(args);
	return (1);
}

int	check_pipe(t_exec_ctx *c)
{
	if (c->i < c->sh->n_cmd - 1)
	{
		if (pipe(c->pipe_fd) < 0)
		{
			perror("pipe");
			return (-1);
		}
	}
	return (0);
}

void	init_exec_ctx(t_exec_ctx *c, t_shell *sh)
{
	c->sh = sh;
	c->node = sh->cmd_head;
	c->i = 0;
	c->prev_fd = -1;
}

int	try_fork_and_run(t_exec_ctx *c)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		return (-1);
	}
	else if (pid == 0)
		child_exec(c);
	parent_after_fork(c, pid);
	return (0);
}

void	launch_process(t_shell *sh)
{
	t_exec_ctx	c;

	if (run_single_builtin_if_alone(sh))
		return ;
	init_exec_ctx(&c, sh);
	while (c.i < sh->n_cmd)
	{
		if (check_pipe(&c) < 0)
			return ;
		if (try_fork_and_run(&c) < 0)
			return ;
		c.i++;
	}
	wait_all_update_status(sh);
	update_last_pid_env(sh);
}

/*
int	start_cmd(t_shell *shell, int *prev_pipe, int *curr_pipe, t_list *curr_cmd)
{
	int		pid;
	t_token	*tok;
	t_cmd	tmp;

	if (shell->fd_in == -1)
		shell->fd_in = STDIN_FILENO;
	if (pipe(shell->fd_pid) == -1)
		perror("fd_pid");
	pid = fork();
	if (pid < 0)
		perror("Forks");
	if (pid == 0)
	{
		add_pid_env(shell, shell->fd_pid[0]);
		dup2(shell->fd_in, STDIN_FILENO);
		close(shell->fd_in);
		dup2(curr_pipe[1], STDOUT_FILENO);
		close(curr_pipe[0]);
		close(curr_pipe[1]);
		close(shell->fd_pid[0]);
		close(shell->fd_pid[1]);
		tok = (t_token *)curr_cmd->content;
		tmp = {0};
		tmp.r = tok->r;
		tmp.r_count = tok->r_count;
		if (apply_redirs_in_child(&tmp, shell))
			_exit(1);
		execute_cmd(shell, tok);
		_exit(1);
	}
	if (shell->fd_in != STDIN_FILENO)
		close(shell->fd_in);
	send_pid(shell->fd_pid[1], pid);
	close(curr_pipe[1]);
	close(shell->fd_pid[0]);
	close(shell->fd_pid[1]);
	prev_pipe[0] = curr_pipe[0];
	prev_pipe[1] = curr_pipe[1];
	curr_cmd = curr_cmd->next;
	return (pid);
}

int	end_cmd(t_shell *shell, int *prev_pipe, t_list *curr_cmd)
{
	int		pid;
	t_token	*tok;
	t_cmd	tmp;

	(void) curr_cmd;
	if (shell->fd_out == -1)
		shell->fd_out = STDOUT_FILENO;
	pid = fork();
	if (pid < 0)
		perror("Forks");
	if (pid == 0)
   {
		add_pid_env(shell, shell->fd_pid[0]);
		close(shell->fd_pid[0]);
		close(shell->fd_pid[1]);
		dup2(prev_pipe[0], STDIN_FILENO);
		close(prev_pipe[0]);
		close(prev_pipe[1]);
		dup2(shell->fd_out, STDOUT_FILENO);
		close(shell->fd_out);
		tok = (t_token *)curr_cmd->content;
		tmp = {0};
		tmp.r = tok->r;
		tmp.r_count = tok->r_count;
		if (apply_redirs_in_child(&tmp, shell))
			_exit(1);
		execute_cmd(shell, tok);
		_exit(1);
	}
	send_pid(shell->fd_pid[1], pid);
	close(shell->fd_pid[0]);
	close(shell->fd_pid[1]);
	close(prev_pipe[0]);
	close(prev_pipe[1]);
	if (shell->fd_out != STDOUT_FILENO)
		close(shell->fd_out);
	return (pid);
}

void	one_command(t_shell *shell)
{
	int		fd[2];
	int		fd_pid[2];
	int		pid;
	t_token	*tok;
	t_cmd	tmp;

	if (shell->fd_in == -1)
		shell->fd_in = STDIN_FILENO;
	if (shell->fd_out == -1)
		shell->fd_out = STDOUT_FILENO;
	if (pipe(fd) == -1 || pipe(fd_pid) == -1) {
		perror("pipe failed");
	}
	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		return ;
	}
	if (pid == 0)
	{
		close(fd[1]);
		close(fd_pid[0]);
		add_pid_env(shell, fd_pid[0]);
		close(fd[0]);
		close(fd_pid[0]);
		dup2(shell->fd_in, STDIN_FILENO);
		close(shell->fd_in);
		dup2(shell->fd_out, STDOUT_FILENO);
		close(shell->fd_out);
		// execute_cmd(shell, shell->parser.cmd_head);
		tok = (t_token *)shell->cmd_head->content;
		tmp = {0};
		tmp.r = tok->r;
		tmp.r_count = tok->r_count;
		if (apply_redirs_in_child(&tmp, shell))
			_exit(1);
		execute_cmd(shell, tok);
		_exit(1);
	}
	else
	close(fd[0]);  // Close read end
	close(fd_pid[0]);
	send_pid(fd_pid[1], pid);
	close(fd[1]);  // Close write end
	close(fd_pid[1]);
	waitpid(pid, NULL, 0); // On attend le process
}


void	launch_process(t_shell *shell)
{
	t_list  *curr_cmd = shell->cmd_head;
	int      prev_fd  = -1;
	int      pipe_fd[2];


	if (shell->n_cmd == 1)
	{
		char **args = expand_cmd((t_token *)curr_cmd->content, shell->env);
		if (args)
		{
			int idx = is_in_t_arr_str(shell->bcmd, args[0]);
			if (idx != -1)
			{
				int (*handler)(t_shell *,
						char **) = get_builtin_handler(shell->bcmd, idx);
				if (handler)
					shell->exit_status = handler(shell, args);
				free_tab(args);
				return ;
			}
			free_tab(args);
		}
	}

	for (int i = 0; i < shell->n_cmd; i++)
	{

		if (i < shell->n_cmd - 1)
		{
			if (pipe(pipe_fd) < 0)
			{
				perror("pipe");
				return ;
			}
		}

		pid_t pid = fork();
		if (pid < 0)
		{
			perror("fork");
			return ;
		}
		else if (pid == 0)
		{

			if (prev_fd != -1)
			{
				dup2(prev_fd, STDIN_FILENO);
				close(prev_fd);
			}
			if (i < shell->n_cmd - 1)
			{
				dup2(pipe_fd[1], STDOUT_FILENO);
				close(pipe_fd[0]);
				close(pipe_fd[1]);
			}
			t_token *tok = (t_token *)curr_cmd->content;
			t_cmd    tmp = {0};
			tmp.r = tok->r;
			tmp.r_count = tok->r_count;
			if (apply_redirs_in_child(&tmp, shell))
				_exit(1);
			execute_cmd(shell, tok);
			_exit(EXIT_FAILURE);
		}


		shell->pids[i] = pid;
		if (prev_fd != -1)
			close(prev_fd);
		if (i < shell->n_cmd - 1)
		{
			close(pipe_fd[1]);
			prev_fd = pipe_fd[0];
		}
		else
			prev_fd = -1;
		curr_cmd = curr_cmd->next;
	}

	int status = 0;
	for (int i = 0; i < shell->n_cmd; i++)
	{
		waitpid(shell->pids[i], &status, 0);
		if (i == shell->n_cmd - 1)
		{
			if (WIFEXITED(status))
				shell->exit_status = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				shell->exit_status = 128 + WTERMSIG(status);
		}
	}


	char pid_str[20];
	snprintf(pid_str, sizeof(pid_str), "%d", (int)shell->pids[shell->n_cmd
		- 1]);
	replace_or_add_env(&shell->env, "PID", pid_str);


}*/
