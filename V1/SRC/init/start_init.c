/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiefer <nkiefer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 16:24:19 by eganassi          #+#    #+#             */
/*   Updated: 2025/08/13 15:21:50 by nkiefer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	init_idx(t_shell *shell, char **envp)
{
	shell->env = init_env(envp);
	if (!shell->env)
	{
		perror("Error initializing environment");
		exit(EXIT_FAILURE);
	}
	shell->fd_in = STDIN_FILENO;
	shell->fd_out = STDOUT_FILENO;
	shell->heredoc = NULL;
	shell->n_tokens = 0;
	shell->n_cmd = 0;
	shell->tokens = NULL;
	shell->cmd_head = NULL;
	shell->cmd_tail = NULL;
	shell->pids = NULL;
	shell->fd_pid[0] = -1;
	shell->fd_pid[1] = -1;
	shell->parsed_args = NULL;
	shell->bcmd = NULL;
	shell->oper = NULL;
}

void	init_shell(t_shell *shell, char **envp)
{
	if (!shell || !envp)
		return ;
	shell->args = NULL;
	shell->exit_status = 0;
	shell->input = NULL;
	init_idx(shell, envp);
	init_all_t_arr(shell);
}

int	start_shell(t_shell *shell, char **envp)
{
	if (!shell)
		return (0);
	ft_bzero(shell, sizeof(t_shell));
	init_signals();
	init_shell(shell, envp);
	return (1);
}
