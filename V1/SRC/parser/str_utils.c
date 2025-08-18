/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiefer <nkiefer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 10:43:53 by eganassi          #+#    #+#             */
/*   Updated: 2025/08/16 16:05:59 by nkiefer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*ft_strdup_count(const char *s, int *count)
{
	size_t	len;
	char	*dup;

	if (!s || !count)
		return (NULL);
	len = strlen(s);
	dup = (char *)malloc(len + 1);
	if (!dup)
		return (NULL);
	ft_strncpy(dup, s, len);
	(*count) += len;
	return (dup);
}

void	write_number_into(char *s, long nb)
{
	int		digits;
	long	t;
	int		i;

	digits = 0;
	t = nb;
	while (t > 0)
	{
		digits++;
		t /= 10;
	}
	i = digits - 1;
	while (nb > 0)
	{
		s[i] = (char)((nb % 10) + '0');
		nb /= 10;
		i--;
	}
	s[digits] = '\0';
}

char	*ft_itoa_inplace(char *s, int n)
{
	char	*start;
	long	nb;

	start = s;
	if (!s)
		return (NULL);
	if (n == 0)
	{
		s[0] = '0';
		s[1] = '\0';
		return (start);
	}
	nb = (long)n;
	if (nb < 0)
	{
		*s = '-';
		s++;
		nb = -nb;
	}
	write_number_into(s, nb);
	return (start);
}
