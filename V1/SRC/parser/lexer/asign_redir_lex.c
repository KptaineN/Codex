/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asign_redir_lex.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiefer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 01:22:52 by nkiefer           #+#    #+#             */
/*   Updated: 2025/08/18 01:22:58 by nkiefer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

/* extrait le nom de fichier et avance i ; NULL si manquant */
char	*extract_fname(t_shell *sh, char **arr, int *i, int op_idx)
{
	char	*op;
	int		len;
	char	*fname;

	op = op_key(sh, op_idx);
	len = sh->parsed_args->len;
	fname = NULL;
	if ((int)ft_strlen(arr[*i]) > (int)ft_strlen(op))
	{
		fname = arr[*i] + ft_strlen(op);
		(*i)++;
	}
	else if (*i + 1 < len)
	{
		fname = arr[*i + 1];
		(*i) += 2;
	}
	return (fname);
}

/* vérifie l'accès fichier via open/close comme dans la version d'origine */
static int	validate_open(int op_idx, char *fname, t_shell *sh)
{
	int	fd;

	fd = -1;
	if (op_idx == 5)
		fd = open(fname, O_RDONLY);
	else if (op_idx == 6)
		fd = open(fname, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else if (op_idx == 1)
		fd = open(fname, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (fd < 0 && op_idx != 0)
	{
		perror(fname);
		sh->exit_status = 1;
		sh->n_tokens = 0;
		return (0);
	}
	if (fd >= 0)
		close(fd);
	return (1);
}

/* affecte le token courant si nécessaire */
static void	maybe_pick_current(t_shell *sh, t_token **cur, int *cmd_idx)
{
	if (!*cur && *cmd_idx < sh->n_tokens)
		*cur = &sh->tokens[(*cmd_idx)++];
}

int	assign_redirs_iter(t_shell *sh, t_token **current, int *cmd_idx, int *i)
{
	char	**arr;
	int		op_idx;
	char	*fname;

	arr = (char **)sh->parsed_args->arr;
	op_idx = is_in_t_arr_dic_str(sh->oper, arr[*i]);
	if (op_idx == -1)
	{
		maybe_pick_current(sh, current, cmd_idx);
		(*i)++;
		return (1);
	}
	if (is_redir_op(op_idx))
	{
		fname = extract_fname(sh, arr, i, op_idx);
		if (!fname || *fname == '\0')
			return (report_missing_fname(sh));
		if (!validate_open(op_idx, fname, sh))
			return (0);
		push_redir_if_current(*current, op_idx, fname);
		return (1);
	}
	*current = NULL;
	(*i)++;
	return (1);
}

void	assign_redirs(t_shell *sh)
{
	t_token	*current;
	int		cmd_idx;
	int		i;

	if (!sh || !sh->parsed_args || !sh->parsed_args->arr)
		return ;
	current = NULL;
	cmd_idx = 0;
	i = 0;
	while (i < sh->parsed_args->len)
	{
		if (!assign_redirs_iter(sh, &current, &cmd_idx, &i))
			return ;
	}
}
