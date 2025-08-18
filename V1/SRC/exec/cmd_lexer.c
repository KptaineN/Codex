/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_lexer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiefer <nkiefer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 01:25:24 by nkiefer           #+#    #+#             */
/*   Updated: 2025/08/18 01:40:39 by nkiefer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * Build a linked list of command tokens from the array of tokens
 * produced during parsing. Only command or builtin tokens are kept
 * and the resulting list is stored in shell->cmd_head.
 */
void	build_cmd_list(t_shell *shell)
{
	t_token	*prev;
	int		i;
	t_token	*tok;

	if (!shell || !shell->tokens)
		return ;
	shell->cmd_head = NULL;
	shell->cmd_tail = NULL;
	shell->n_cmd = 0;
	prev = NULL;
	i = 0;
	while (i < shell->n_tokens)
	{
		tok = &shell->tokens[i];
		if (tok->type == TOKEN_CMD || tok->type == TOKEN_BCMD)
		{
			if (prev)
				prev->next = tok;
			tok->next = NULL;
			add_cmd(shell, tok);
			prev = tok;
			shell->n_cmd++;
		}
		i++;
	}
}

/* op de redirection : <<, >>, <, > (pas | ni séparateurs 2..4) */
static int	is_redir_op_idx(int op_idx)
{
	return (op_idx < 2 || op_idx > 4);
}

/* saute l'opérateur de redirection (+ son éventuel filename séparé) */
static int	skip_redir_token(t_shell *sh, char **arr, int i, int op_idx)
{
	t_dic	*d;

	d = (t_dic *)sh->oper->arr[op_idx];
	if ((int)ft_strlen(arr[i]) == (int)ft_strlen(d->key))
		i++;
	i++;
	return (i);
}

static int	count_args_core(t_shell *sh, char **arr, int i, int len)
{
	int	n_args;
	int	op_idx;

	n_args = 0;
	while (i < len && arr[i])
	{
		op_idx = is_in_t_arr_dic_str(sh->oper, arr[i]);
		if (op_idx != -1)
		{
			if (is_redir_op_idx(op_idx))
				i = skip_redir_token(sh, arr, i, op_idx);
			else
				break ;
		}
		else
		{
			n_args++;
			i++;
		}
	}
	return (n_args);
}

int	count_args_cmd(t_shell *sh, int i)
{
	char	**arr;
	int		len;
	int		n;

	if (!sh || !sh->parsed_args || !sh->parsed_args->arr)
		return (0);
	arr = (char **)sh->parsed_args->arr;
	len = sh->parsed_args->len;
	n = count_args_core(sh, arr, i, len);
	if (n == 0)
		return (1);
	return (n);
}
