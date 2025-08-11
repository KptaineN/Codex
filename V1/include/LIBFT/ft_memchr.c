/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiefer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 14:41:51 by nkiefer           #+#    #+#             */
/*   Updated: 2024/10/30 18:52:06 by nkiefer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *str, int c, size_t n)
{
	const unsigned char	*ptr;
	unsigned char		un_c;

	ptr = (const unsigned char *) str;
	un_c = (unsigned char) c;
	while (n--)
	{
		if (*ptr == un_c)
		{
			return ((void *)ptr);
		}
		ptr++;
	}
	return (NULL);
}
