/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util-2-free.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkief <nkief@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 16:30:45 by eganassi          #+#    #+#             */
/*   Updated: 2025/08/20 12:03:30 by nkief            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "../env/env.h"

void	free_t_arr_dic(t_arr *array)
{
	t_dic	*dic;
	int		i;

	if (!array)
		return ;
	if (array->arr)
	{
		i = 0;
		while (i < array->len)
		{
			dic = (t_dic *)array->arr[i];
			if (dic)
			{
				if (dic->key)
					free(dic->key);
				free(dic);
			}
			i++;
		}
		free(array->arr);
	}
	free(array);
}

void	free_t_arr(t_arr *array)
{
	int	i;

	if (!array)
		return ;
	if (array->arr)
	{
		i = 0;
		while (i < array->len)
		{
			free(array->arr[i]);
			i++;
		}
		free(array->arr);
	}
	free(array);
}

void	free_list_str(t_list *lst)
{
	t_list	*tmp;

	while (lst)
	{
		tmp = lst->next;
		if (lst->content)
			free(lst->content);
		free(lst);
		lst = tmp;
	}
}

void	free_parser(t_shell *parser)
{
	if (!parser)
		return ;
	if (parser->parsed_args)
		free_t_arr(parser->parsed_args);
	parser->parsed_args = NULL;
	if (parser->bcmd)
		free_t_arr_dic(parser->bcmd);
	parser->bcmd = NULL;
	if (parser->oper)
		free_t_arr_dic(parser->oper);
	parser->oper = NULL;
	if (parser->env)
		free_env_list(parser->env);
	parser->env = NULL;
}

void	free_minishell(t_shell *shell)
{
	if (!shell)
		return ;
	free_parser(shell);
	if (shell->args)
		free_str_array(shell->args);
	shell->args = NULL;
}
