/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subtoken.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiefer <nkiefer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 17:04:22 by nkiefer           #+#    #+#             */
/*   Updated: 2025/08/18 01:09:52 by nkiefer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../token.h"

static void	handle_single_quoted(t_stctx *st)
{
	int	start;
	int	tail;

	start = st->idx + 1;
	tail = find_c_nonescaped((char *)&st->arg[start], "\'", 1);
	if (tail < 0)
		tail = st->arg_len - start;
	st->parts[st->i].type = QUOTE_SINGLE;
	st->parts[st->i].p = ft_substr(st->arg, start, tail);
	st->parts[st->i].len = tail;
	st->idx = start + tail + 1;
	st->i++;
}

static void	handle_double_quoted(t_stctx *st)
{
	int	start;
	int	tail;

	start = st->idx + 1;
	tail = find_c_nonescaped((char *)&st->arg[start], "\"", 1);
	if (tail < 0)
		tail = st->arg_len - start;
	st->parts[st->i].type = QUOTE_DOUBLE;
	st->parts[st->i].p = ft_substr(st->arg, start, tail);
	st->parts[st->i].len = tail;
	st->idx = start + tail + 1;
	st->i++;
}

static void	handle_unquoted(t_stctx *st)
{
	int	start;
	int	tail;

	start = st->idx;
	tail = find_c_nonescaped((char *)&st->arg[start], "\"\'", 2);
	if (tail < 0)
		tail = st->arg_len - start;
	st->parts[st->i].type = QUOTE_NONE;
	st->parts[st->i].p = ft_substr(st->arg, start, tail);
	st->parts[st->i].len = tail;
	st->idx = start + tail;
	st->i++;
}

void	subtoken_of_cmd(t_subtoken_container *container, char *arg)
{
	t_stctx	st;

	if (!container || !arg || container->n_parts <= 0)
		return ;
	st.arg = arg;
	st.arg_len = ft_strlen(arg);
	st.idx = 0;
	st.i = 0;
	st.parts = container->parts;
	while (st.idx < st.arg_len && st.i < container->n_parts)
	{
		if (arg[st.idx] == '\'' && escape_check(arg, st.idx))
			handle_single_quoted(&st);
		else if (arg[st.idx] == '\"' && escape_check(arg, st.idx))
			handle_double_quoted(&st);
		else
			handle_unquoted(&st);
	}
}
