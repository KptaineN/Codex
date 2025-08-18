/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   attribution_subok.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiefer <nkiefer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 01:18:26 by nkiefer           #+#    #+#             */
/*   Updated: 2025/08/18 01:21:24 by nkiefer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../token.h"

static int	is_redir_idx(int op_idx)
{
	return (op_idx != -1 && (op_idx < 2 || op_idx > 4));
}

static int	skip_redir(t_shell *sh, char **args, int idx, int op_idx)
{
	t_dic	*d;

	d = (t_dic *)sh->oper->arr[op_idx];
	if ((int)ft_strlen(args[idx]) == (int)ft_strlen(d->key))
		idx++;
	idx++;
	return (idx);
}

void	fill_container(t_subtoken_container *c, const char *arg)
{
	c->n_parts = count_subtokens(arg);
	if (c->n_parts > 0)
	{
		c->parts = malloc(sizeof(t_subtoken) * c->n_parts);
		subtoken_of_cmd(c, (char *)arg);
	}
}

void	process_slot(t_shell *sh, t_subtoken_container *conts, char **args,
		t_it *it)
{
	int	op_idx;

	op_idx = is_in_t_arr_dic_str(sh->oper, args[it->idx]);
	if (is_redir_idx(op_idx))
	{
		it->idx = skip_redir(sh, args, it->idx, op_idx);
		return ;
	}
	fill_container(&conts[it->k], args[it->idx]);
	it->idx++;
	it->k++;
}

int	attribute_cmd_subtokens(t_shell *sh, t_token *cmd_token, int idx, int len)
{
	t_arr					*arr_arg;
	char					**args;
	t_subtoken_container	*conts;
	t_it					it;

	if (!sh || !cmd_token || !sh->parsed_args || !sh->parsed_args->arr)
		return (idx + 1);
	if (len <= 0)
		return (idx + 1);
	arr_arg = sh->parsed_args;
	args = (char **)arr_arg->arr;
	conts = calloc(len + 1, sizeof(t_subtoken_container));
	if (!conts)
		return (idx + len);
	cmd_token->cmd_args_parts = conts;
	cmd_token->n_args = len;
	it.idx = idx;
	it.k = 0;
	while (it.k < len && it.idx < arr_arg->len)
		process_slot(sh, conts, args, &it);
	conts[len].n_parts = 0;
	conts[len].parts = NULL;
	return (it.idx);
}
