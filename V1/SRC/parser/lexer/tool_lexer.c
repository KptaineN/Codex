/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tool_lexer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiefer <nkiefer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 22:24:17 by eganassi          #+#    #+#             */
/*   Updated: 2025/08/18 00:42:10 by nkiefer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

/* helper: test si c'est un opérateur de redirection (pas | ni sépa) */
int	is_redir_op(int op_idx)
{
	return (op_idx < 2 || op_idx > 4);
}

/* helper: récupérer la chaîne opérateur depuis le dictionnaire */
char	*op_key(t_shell *sh, int op_idx)
{
	t_dic	*d;

	d = (t_dic *)sh->oper->arr[op_idx];
	return (d->key);
}

/* message d'erreur + statut quand nom manquant */
int	report_missing_fname(t_shell *sh)
{
	ft_putstr_fd("minishell: missing file name for redirection\n",
		STDERR_FILENO);
	sh->exit_status = 1;
	sh->n_tokens = 0;
	return (0);
}

bool	escape_check(const char *str, int idx)
{
	bool	toggle;

	toggle = true;
	while (idx > 0 && str[--idx] == '\\')
		toggle = !toggle;
	return (toggle);
}

int	find_c_nonescaped(const char *str, char *needle, int size_needle)
{
	int	c;
	int	idx;

	idx = 0;
	while (str[idx])
	{
		c = 0;
		while (c < size_needle && str[idx])
		{
			if (str[idx] == needle[c] && escape_check(str, idx))
				return (idx);
			c++;
		}
		idx++;
	}
	return (idx);
}
