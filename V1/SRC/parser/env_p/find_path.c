/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_env_value.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiefer <nkiefer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 14:54:24 by nkiefer           #+#    #+#             */
/*   Updated: 2025/08/16 14:55:39 by nkiefer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

char	*check_dir_for_cmd(char *dir, char *cmd)
{
	char	*full;

	full = NULL;
	full = join_path(dir, cmd);
	if (!full)
		return (NULL);
	if (access(full, F_OK | X_OK) == 0)
		return (full);
	free(full);
	return (NULL);
}

char	*scan_path_copy(char *cmd, char *copy)
{
	char	*p;
	char	*q;
	char	c;
	char	*hit;

	p = NULL;
	q = NULL;
	hit = NULL;
	p = copy;
	while (1)
	{
		q = p;
		while (*q && *q != ':')
			q++;
		c = *q;
		*q = '\0';
		if (*p != '\0')
			hit = check_dir_for_cmd(p, cmd);
		*q = c;
		if (hit || c == '\0')
			break ;
		p = q + 1;
	}
	return (hit);
}

char	*search_in_path(char *cmd, char *path_env)
{
	char	*copy;
	char	*hit;

	copy = NULL;
	hit = NULL;
	if (!path_env)
		return (NULL);
	copy = ft_strdup(path_env);
	if (!copy)
		return (NULL);
	hit = scan_path_copy(cmd, copy);
	free(copy);
	return (hit);
}

char	*find_command_path(char *cmd, t_list *env)
{
	char	*path_env;
	char	*direct;
	char	*found;

	path_env = NULL;
	direct = NULL;
	found = NULL;
	if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, F_OK | X_OK) == 0)
			return (ft_strdup(cmd));
		return (NULL);
	}
	path_env = get_path_env(env);
	if (!path_env)
		return (NULL);
	found = search_in_path(cmd, path_env);
	if (found)
		return (found);
	return (NULL);
}
