/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiefer <nkiefer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 17:28:49 by nkiefer           #+#    #+#             */
/*   Updated: 2025/08/16 12:39:45 by nkiefer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "go_away.h"

void	ctx_init(t_stx *c)
{
	c->in_sq = false;
	c->in_dq = false;
	c->i = 0;
	c->j = 0;
}

int	try_quote(const char *s, t_stx *c, char *out)
{
	char	ch;

	ch = s[c->i];
	if (!((ch == '\'' && !c->in_dq) || (ch == '"' && !c->in_sq)))
		return (0);
	if (ch == '\'' && !c->in_dq)
		c->in_sq = !c->in_sq;
	else if (ch == '"' && !c->in_sq)
		c->in_dq = !c->in_dq;
	if (out)
	{
		out[c->j] = s[c->i];
		c->j++;
	}
	c->i++;
	return (1);
}

int	try_exit(const char *s, t_stx *c, char *out, t_rep *r)
{
	if (!(c->in_sq == false && s[c->i] == '$' && s[c->i + 1] == '?'))
		return (0);
	if (out && r)
	{
		ft_memcpy(out + c->j, r->code, r->clen);
		c->j += r->clen;
	}
	else
		c->j++;
	c->i += 2;
	return (1);
}

char	*fill_with_replacement(const char *input, const char *code_str,
		size_t out_len)
{
	t_stx	c;
	t_rep	r;
	char	*res;
	bool	handled;

	ctx_init(&c);
	r.code = code_str;
	r.clen = ft_strlen(code_str);
	res = (char *)malloc(out_len + 1);
	if (!res)
		return (NULL);
	while (input[c.i])
	{
		handled = try_quote(input, &c, res);
		if (!handled)
			handled = try_exit(input, &c, res, &r);
		if (!handled)
			res[c.j++] = input[c.i++];
	}
	res[c.j] = '\0';
	return (res);
}
