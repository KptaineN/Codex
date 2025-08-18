/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiefer <nkiefer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 22:41:19 by eganassi          #+#    #+#             */
/*   Updated: 2025/08/18 01:42:44 by nkiefer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

bool	is_command(char *str, t_list *env)
{
	char	*cmd_path;

	cmd_path = find_command_path(str, env);
	if (cmd_path)
	{
		free(cmd_path);
		return (1);
	}
	return (0);
}

void	add_cmd(t_shell *shell, t_token *token)
{
	t_list	*tmp;

	tmp = malloc(sizeof(t_list));
	if (!tmp)
	{
		perror("Erreur malloc add_cmd");
		return ;
	}
	tmp->content = (void *)token;
	tmp->next = NULL;
	if (!shell->cmd_head)
	{
		shell->cmd_head = tmp;
		shell->cmd_tail = tmp;
	}
	else
	{
		shell->cmd_tail->next = tmp;
		shell->cmd_tail = tmp;
	}
}
