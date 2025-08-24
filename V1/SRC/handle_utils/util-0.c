/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util-0.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiefer <kiefer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 16:30:56 by eganassi          #+#    #+#             */
/*   Updated: 2025/08/18 06:04:48 by kiefer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cleanup_shell_iter(t_shell *sh)
{
	if (sh->parsed_args)
	{
		free_str_array((char **)sh->parsed_args->arr);
		free(sh->parsed_args);
		sh->parsed_args = NULL;
	}
	free_cmd_list(sh);
	free_tokens(sh);
	free(sh->pids);
	sh->pids = NULL;
}

char	*ft_strjoin3(char *a, const char *b, const char *c, int free_a)
{
	char	*tmp;
	char	*res;

	if (!a || !b || !c)
		return (NULL);
	tmp = ft_strjoin(a, b);
	if (!tmp)
		return (NULL);
	res = ft_strjoin(tmp, c);
	free(tmp);
	if (free_a)
		free(a);
	return (res);
}

static void	child_cleanup_shell(t_shell *sh)
{
	if (!sh)
		return ;
	if (sh->exec_envp_tmp)
		free_str_array(sh->exec_envp_tmp);
	if (sh->exec_cmd_path_tmp)
		free(sh->exec_cmd_path_tmp);
	if (sh->exec_candidates_tmp)
		free_list_str(sh->exec_candidates_tmp);
	sh->exec_envp_tmp = NULL;
	sh->exec_cmd_path_tmp = NULL;
	sh->exec_candidates_tmp = NULL;
}

void	exit_child_process(t_shell *sh, int code)
{
	child_cleanup_shell(sh);
	exit(code);
}

void	handle_builtin(t_shell *shell)
{
	size_t	len;

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
	{
		len = ft_strlen(shell->args[0]);
		write(2, shell->args[0], len);
		write(2, ": command not found\n", sizeof(": command not found\n") - 1);
	}
}
