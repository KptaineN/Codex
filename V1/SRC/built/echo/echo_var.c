/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_var.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiefer <nkiefer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 15:36:18 by nkiefer           #+#    #+#             */
/*   Updated: 2025/08/13 21:57:30 by nkiefer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "echo.h"

static int	write_dollar(char *dst, int *i)
{
	int	written;

	written = 1;
	dst[0] = '$';
	(*i)++;
	return (written);
}

static int	handle_dollar(char *res, const char *arg, int *i, t_shell *sh)
{
	char	*val;
	int		nb;

	val = get_dollar_value(arg, i, sh);
	if (!val)
	{
		return (0);
	}
	nb = ft_strlen(val);
	if (nb)
		ft_memcpy(res, val, nb);
	free(val);
	return (nb);
}

int	dollar_edge_cases(char *dst, const char *arg, int *i, t_shell *sh)
{
	int		k;
	char	c;

	k = *i + 1;
	c = arg[k];
	if (c == '\0')
		return (write_dollar(dst, i));
	if (c == '?')
		return (write_and_free(dst, ft_itoa(sh->exit_status), i, k + 1));
	if (!is_valid_key_char((unsigned char)c))
		return (write_dollar(dst, i));
	return (-1);
}

int	process_dollar(char *dst, const char *arg, int *i, t_shell *sh)
{
	int	handled;

	handled = dollar_edge_cases(dst, arg, i, sh);
	if (handled >= 0)
		return (handled);
	return (handle_dollar(dst, arg, i, sh));
}

char	*replace_variables(const char *arg, t_shell *sh)
{
	int		i;
	int		j;
	bool	in_sq;
	bool	in_dq;
	char	*res;

	in_sq = false;
	in_dq = false;
	i = 0;
	j = 0;
	res = malloc(ft_strlen(arg) * 50 + 1);
	if (!res)
		return (NULL);
	while (arg[i])
	{
		toggle_quotes(arg[i], &in_sq, &in_dq);
		if (arg[i] == '$' && !in_sq)
			j += process_dollar(&res[j], arg, &i, sh);
		else
			res[j++] = arg[i++];
	}
	res[j] = '\0';
	return (res);
}
