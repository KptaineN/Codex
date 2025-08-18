/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiefer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 01:18:05 by nkiefer           #+#    #+#             */
/*   Updated: 2025/08/18 01:18:08 by nkiefer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"

void	token_set_value_or_die(t_token *tok, char **args, int i)
{
	tok->value = ft_strdup(args[i]);
	if (!tok->value)
	{
		perror("Erreur allocation token value");
		exit(EXIT_FAILURE);
	}
}

int	is_operator_here(t_shell *sh, char **args, int i)
{
	return (is_in_t_arr_dic_str(sh->oper, args[i]) != -1);
}

int	process_operator_token(t_token *tok, int i)
{
	tok->type = TOKEN_OPER;
	return (i + 1);
}

int	advance_after_operator(t_shell *sh, t_arr *parsed_args, int i, int op_idx)
{
	int	consumed;

	if (op_idx < 2 || op_idx > 4)
	{
		consumed = file_access_redirection(sh, parsed_args->arr, op_idx, i);
		return (i + consumed);
	}
	return (i + 1);
}

/* commande → avance de n_args comme dans la version d'origine */
int	advance_after_command(t_shell *sh, int i)
{
	int	n_args;

	n_args = count_args_cmd(sh, i);
	return (i + n_args);
}
