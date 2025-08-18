/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util-4-free-token.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiefer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 23:03:28 by nkiefer           #+#    #+#             */
/*   Updated: 2025/08/13 23:03:32 by nkiefer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	free_subtoken_parts(t_subtoken_container *cont)
{
	int	k;

	if (!cont || !cont->parts)
		return ;
	k = 0;
	while (k < cont->n_parts)
	{
		cont->parts[k].p = NULL;
		k++;
	}
	free(cont->parts);
	cont->parts = NULL;
	cont->n_parts = 0;
}

static void	free_cmd_args_parts(t_token *tok)
{
	int	j;

	if (!tok || !tok->cmd_args_parts)
		return ;
	j = 0;
	while (j < tok->n_args)
	{
		free_subtoken_parts(&tok->cmd_args_parts[j]);
		j++;
	}
	free(tok->cmd_args_parts);
	tok->cmd_args_parts = NULL;
	tok->n_args = 0;
}

static void	free_redirs(t_token *tok)
{
	int	j;

	if (!tok || !tok->r)
		return ;
	j = 0;
	while (j < tok->r_count)
	{
		if (tok->r[j].arg)
			free(tok->r[j].arg);
		tok->r[j].arg = NULL;
		j++;
	}
	free(tok->r);
	tok->r = NULL;
	tok->r_count = 0;
}

static void	free_one_token(t_token *tok)
{
	if (!tok)
		return ;
	free_cmd_args_parts(tok);
	free_redirs(tok);
	if (tok->value)
		free(tok->value);
	tok->value = NULL;
}

void	free_tokens(t_shell *shell)
{
	int	i;

	if (!shell || !shell->tokens)
		return ;
	i = 0;
	while (i < shell->n_tokens)
	{
		free_one_token(&shell->tokens[i]);
		i++;
	}
	free(shell->tokens);
	shell->tokens = NULL;
	shell->n_tokens = 0;
}
