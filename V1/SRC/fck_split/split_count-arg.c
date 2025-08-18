/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_count-arg.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiefer <nkiefer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 15:25:11 by nkiefer           #+#    #+#             */
/*   Updated: 2025/08/16 15:40:58 by nkiefer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "split.h"

/* =============================
 * Compte le nombre d'arguments
 * ============================= */
void	toggle_quotes_ctx(t_scan_ctx *s)
{
	if (s->str[s->i] == '\'' && !s->in_dq && escape_check(s->str, s->i))
		s->in_sq = !s->in_sq;
	else if (s->str[s->i] == '"' && !s->in_sq && escape_check(s->str, s->i))
		s->in_dq = !s->in_dq;
}

void	flush_on_space_ctx(t_scan_ctx *s)
{
	if (s->str[s->i] == ' ' && !s->in_sq && !s->in_dq && s->in_word)
	{
		s->count++;
		s->in_word = false;
	}
}

void	handle_oper_or_word_ctx(t_scan_ctx *s)
{
	int		idx_oper;
	int		keylen;
	t_dic	*dic;

	idx_oper = -1;
	keylen = 0;
	idx_oper = is_in_t_arr_dic_str(s->shell->oper, (char *)&s->str[s->i]);
	if (idx_oper != -1)
	{
		if (s->in_word)
		{
			s->count++;
			s->in_word = false;
		}
		dic = (t_dic *)s->shell->oper->arr[idx_oper];
		keylen = ft_strlen((char *)dic->key);
		s->count++;
		s->i += keylen - 1;
	}
	else if (!s->in_word)
		s->in_word = true;
}

void	handle_count_char_ctx(t_scan_ctx *s)
{
	toggle_quotes_ctx(s);
	if (!s->in_sq && !s->in_dq)
	{
		flush_on_space_ctx(s);
		if (s->str[s->i] != ' ')
			handle_oper_or_word_ctx(s);
	}
	else if (!s->in_word)
		s->in_word = true;
}

int	count_arg(const char *str, t_shell *shell)
{
	t_scan_ctx	s;

	s.str = str;
	s.shell = shell;
	s.i = 0;
	s.count = 0;
	s.in_sq = false;
	s.in_dq = false;
	s.in_word = false;
	while (s.str[s.i])
	{
		handle_count_char_ctx(&s);
		s.i++;
	}
	if (s.in_word)
		s.count++;
	return (s.count);
}
