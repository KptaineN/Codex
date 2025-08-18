/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiefer <nkiefer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 16:35:41 by eganassi          #+#    #+#             */
/*   Updated: 2025/08/16 16:36:21 by nkiefer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	run_builtin_if_any(t_shell *shell, char **args)
{
	int	idx;
	int	(*handler)(t_shell *, char **);

	idx = is_in_t_arr_str(shell->bcmd, args[0]);
	if (idx == -1)
		return (0);
	handler = get_builtin_handler(shell->bcmd, idx);
	if (!handler)
		exit_child_process(shell, 1);
	shell->exit_status = handler(shell, args);
	exit(shell->exit_status);
	return (1);
}

void	print_cmd_not_found(const char *s)
{
	size_t	len;

	len = ft_strlen(s);
	write(2, s, len);
	write(2, ": command not found\n", 21);
}

/* impl */
char	*resolve_cmd_path_or_die(t_shell *shell, char *name)
{
	char	*path;

	path = find_command_path(name, shell->env);
	if (!path)
	{
		print_cmd_not_found(name);
		exit_child_process(shell, 127);
	}
	return (path);
}

void	prepare_or_run_builtin(t_shell *shell, t_token *cmd, char ***out_args)
{
	char	**args;
	int		(*handler)(t_shell *, char **);

	if (!cmd || !cmd->value)
		exit_child_process(shell, 1);
	args = expand_cmd(cmd, shell->env);
	if (!args || !args[0])
	{
		write(2, cmd->value, ft_strlen(cmd->value));
		write(2, ": command not found\n", 21);
		exit_child_process(shell, 127);
	}
	if (is_in_t_arr_str(shell->bcmd, args[0]) != -1)
	{
		handler = get_builtin_handler(shell->bcmd, is_in_t_arr_str(shell->bcmd,
					args[0]));
		if (!handler)
			exit_child_process(shell, 1);
		shell->exit_status = handler(shell, args);
		exit(shell->exit_status);
	}
	*out_args = args;
}

void	execute_cmd(t_shell *shell, t_token *cmd)
{
	char	**args;
	char	*cmd_path;
	char	**envp;

	prepare_or_run_builtin(shell, cmd, &args);
	cmd_path = find_command_path(args[0], shell->env);
	if (!cmd_path)
	{
		write(2, args[0], ft_strlen(args[0]));
		write(2, ": command not found\n", 21);
		exit_child_process(shell, 127);
	}
	envp = list_to_envp(shell->env);
	if (!envp)
	{
		perror("envp");
		exit_child_process(shell, 1);
	}
	execve(cmd_path, args, envp);
	perror("execve");
	exit_child_process(shell, 127);
}
