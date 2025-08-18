/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_quote.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiefer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 21:58:41 by nkiefer           #+#    #+#             */
/*   Updated: 2025/08/13 21:58:46 by nkiefer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "echo.h"

void	toggle_quotes(char c, bool *in_sq, bool *in_dq)
{
	if (c == '\'' && !(*in_dq))
		*in_sq = !(*in_sq);
	else if (c == '"' && !(*in_sq))
		*in_dq = !(*in_dq);
}

static int	rq_handle_quote(char c, bool *in_sq, bool *in_dq)
{
	if (c == '\'' && !*in_dq)
	{
		*in_sq = !*in_sq;
		return (1);
	}
	if (c == '"' && !*in_sq)
	{
		*in_dq = !*in_dq;
		return (1);
	}
	return (0);
}

static char	*rq_alloc(const char *arg)
{
	return ((char *)malloc(ft_strlen(arg) + 1));
}

char	*remove_quotes(const char *arg)
{
	size_t	i;
	size_t	j;
	bool	in_sq;
	bool	in_dq;
	char	*res;

	i = 0;
	j = 0;
	in_sq = false;
	in_dq = false;
	res = rq_alloc(arg);
	if (!res)
		return (NULL);
	while (arg[i])
	{
		if (rq_handle_quote(arg[i], &in_sq, &in_dq))
			i++;
		else
			res[j++] = arg[i++];
	}
	res[j] = '\0';
	return (res);
}
