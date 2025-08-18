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

