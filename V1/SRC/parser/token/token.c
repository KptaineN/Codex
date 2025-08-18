/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiefer <nkiefer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 17:04:27 by nkiefer           #+#    #+#             */
/*   Updated: 2025/08/18 01:20:47 by nkiefer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"

/* opérateur → avance l'index comme dans la version d'origine */
int	count_tokens(t_shell *sh, t_arr *parsed_args, t_arr *oper)
{
	char	**args;
	int		count;
	int		i;
	int		op_idx;

	if (!parsed_args || !parsed_args->arr)
		return (0);
	args = (char **)parsed_args->arr;
	count = 0;
	i = 0;
	while (i < parsed_args->len)
	{
		op_idx = is_in_t_arr_dic_str(oper, args[i]);
		if (op_idx != -1)
		{
			count++;
			i = advance_after_operator(sh, parsed_args, i, op_idx);
		}
		else
		{
			count++;
			i = advance_after_command(sh, i);
		}
	}
	return (count);
}

/* -- helpers -- */

int	setup_tokens_or_return(t_shell *sh)
{
	void	**arr;

	if (!sh || !sh->parsed_args || !sh->parsed_args->arr)
	{
		if (sh)
			sh->n_tokens = 0;
		return (0);
	}
	arr = sh->parsed_args->arr;
	if (sh->parsed_args->len <= 0)
	{
		sh->n_tokens = 0;
		return (0);
	}
	sh->n_tokens = count_tokens(sh, sh->parsed_args, sh->oper);
	sh->tokens = (t_token *)calloc(sh->n_tokens, sizeof(t_token));
	if (!sh->tokens)
	{
		perror("Erreur allocation tokens");
		exit(EXIT_FAILURE);
	}
	return (1);
}

int	process_cmd_or_bcmd(t_shell *sh, t_token *tok, int i)
{
	char	**args;
	int		nb_args;
	int		new_i;

	args = (char **)sh->parsed_args->arr;
	if (is_in_t_arr_str(sh->bcmd, args[i]) != -1)
		tok->type = TOKEN_BCMD;
	else
		tok->type = TOKEN_CMD;
	nb_args = count_args_cmd(sh, i);
	if (!(nb_args > 0))
		nb_args = 1;
	new_i = attribute_cmd_subtokens(sh, tok, i, nb_args);
	if (new_i > i)
		return (new_i);
	else
		return (i + 1);
}

/* -- fonction principale -- */
void	attribute_token_type(t_shell *sh)
{
	char	**args;
	int		i;
	int		idx_token;
	t_token	*tok;

	if (!setup_tokens_or_return(sh))
		return ;
	args = (char **)sh->parsed_args->arr;
	i = 0;
	idx_token = 0;
	while (i < sh->parsed_args->len && idx_token < sh->n_tokens)
	{
		tok = &sh->tokens[idx_token];
		token_set_value_or_die(tok, args, i);
		if (is_operator_here(sh, args, i))
			i = process_operator_token(tok, i);
		else
			i = process_cmd_or_bcmd(sh, tok, i);
		idx_token++;
	}
}
