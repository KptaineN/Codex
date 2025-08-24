/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiefer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 11:59:16 by nkiefer           #+#    #+#             */
/*   Updated: 2024/10/20 12:03:46 by nkiefer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	ft_isalpha(int c)
{
	if (((c >= 'a') && (c <= 'z')) || ((c >= 'A') && (c <= 'Z')))
	{
		return (1);
	}
	return (0);
}
/*#include "libft.h"
#include <stdio.h>
#include <ctype.h> // Pour la fonction standard isalpha

int main(void)
{
    int test_cases[] = {
        'a', 'Z', '0', '9', '!', ' ', '\n', '1', 'b', 'G', 0
    };

    for (int i = 0; test_cases[i] != 0; i++)
    {
        int c = test_cases[i];
        printf("Input: '%c' (ASCII: %d)\n", c, c);
        printf("ft_isalpha: %d\n", ft_isalpha(c));
        printf("isalpha: %d\n", isalpha(c));
        printf("\n");
    }

    return 0;
}*/
