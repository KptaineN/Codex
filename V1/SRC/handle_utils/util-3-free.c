/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util-3-free.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiefer <nkiefer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 16:27:38 by eganassi          #+#    #+#             */
/*   Updated: 2025/08/13 23:19:04 by nkiefer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_str_array(char **arr)
{
	int	i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

void	free_cmd_list(t_shell *shell)
{
	t_list	*node;
	t_list	*next;

	node = shell->cmd_head;
	while (node)
	{
		next = node->next;
		free(node);
		node = next;
	}
	shell->cmd_head = NULL;
	shell->cmd_tail = NULL;
	shell->n_cmd = 0;
}

void	free_subtoken_container(t_subtoken_container *container)
{
	t_subtoken	*sub;
	int			i;

	if (!container)
		return ;
	if (container->parts)
	{
		i = 0;
		while (i < container->n_parts)
		{
			sub = &container->parts[i];
			if (sub->p)
				free(sub->p);
			i++;
		}
		free(container->parts);
	}
	free(container);
}

void	free_tab(char **tab)
{
	int	i;

	if (!tab)
		return ;
	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}
