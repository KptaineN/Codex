/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   advanced_redir.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiefer <nkiefer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 02:23:55 by nkiefer           #+#    #+#             */
/*   Updated: 2025/08/18 02:29:55 by nkiefer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redir.h"

/* ----- expansion simple pour heredoc non quoté ----- */
char	*expand_vars_in_line(const char *line, t_shell *sh)
{
	char	*tmp;
	char	*res;

	if (!line)
		return (NULL);
	tmp = replace_exit_code(line, sh->exit_status);
	res = replace_variables(tmp, sh);
	free(tmp);
	return (res);
}

char	*expand_filename_if_needed(char *arg, t_shell *sh)
{
	char	*tmp;
	char	*res;

	tmp = replace_exit_code(arg, sh->exit_status);
	res = replace_variables(tmp, sh);
	free(tmp);
	return (res);
}

char	*resolve_path(const char *cmd, t_shell *sh)
{
	(void)sh;
	return ((char *)cmd);
}

/* ----- intégration enfant maillon ----- 
void	child_exec_maillon(t_cmd *c, t_shell *sh, int i, int ncmd, int p[][2])
{
	int		k;
	char	**envp;

	if (i > 0)
		dup2(p[i - 1][0], STDIN_FILENO);
	if (i < ncmd - 1)
		dup2(p[i][1], STDOUT_FILENO);
	k = 0;
	while (k < ncmd - 1)
	{
		close(p[k][0]);
		close(p[k][1]);
		k++;
	}
	if (apply_redirs_in_child(c, sh))
		_exit(1);
	if (c->is_builtin)
		_exit(run_builtin_if_any(sh, c->argv));
	envp = list_to_envp(sh->env);
	execve(resolve_path(c->argv[0], sh), c->argv, envp);
	perror("execve");
	_exit(127);
}*/
