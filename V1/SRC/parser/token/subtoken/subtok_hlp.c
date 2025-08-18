/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subtok_hlp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiefer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 01:18:47 by nkiefer           #+#    #+#             */
/*   Updated: 2025/08/18 01:18:52 by nkiefer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../token.h"

static void	process_char(const char *s, int i, t_qstate *st)
{
	if (s[i] == '\"' && !st->in_sq && escape_check(s, i))
	{
		st->in_nq = false;
		st->in_dq = !st->in_dq;
		if (st->in_dq)
			st->count++;
	}
	else if (s[i] == '\'' && !st->in_dq && escape_check(s, i))
	{
		st->in_nq = false;
		st->in_sq = !st->in_sq;
		if (st->in_sq)
			st->count++;
	}
	else if (!st->in_sq && !st->in_dq && !st->in_nq)
	{
		st->count++;
		st->in_nq = true;
	}
}

int	count_subtokens(const char *str)
{
	t_qstate	st;
	int			i;

	st.in_sq = false;
	st.in_dq = false;
	st.in_nq = false;
	st.count = 0;
	i = 0;
	while (str[i])
	{
		process_char(str, i, &st);
		i++;
	}
	return (st.count);
}
