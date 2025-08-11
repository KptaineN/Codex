/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiefer <nkiefer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 10:43:53 by eganassi          #+#    #+#             */
/*   Updated: 2025/07/28 14:20:26 by nkiefer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char *ft_strdup_count(const char *s, int *count)
{
    size_t len;
    char *dup;

    if (!s || !count) // Check for NULL inputs
        return (NULL);

    len = strlen(s);

    dup = (char *)malloc(len + 1); // Allocate for string + null terminator
    if (!dup)
        return (NULL);
    ft_strncpy(dup,s,len);
    (*count)+=len; // Increment the counter
    return (dup);
}

//void ft_swap(void *a, void *b)
//{
//    void *tp;
//    tp = a;
//    b = a;
//    b = tp;
//}

char *ft_itoa_inplace(char *s, int n)
{
    char *start = s;
    char *ptr;
    int digits = 0;
    int temp;

    if (!s)
        return NULL;

    // Handle zero
    if (n == 0)
    {
        s[0] = '0';
        s[1] = '\0';
        return s;
    }

    // Handle negative numbers
    if (n < 0)
    {
        n = -n;
        *s++ = '-'; // Write sign directly
    }

    // Count digits and move to end position
    temp = n;
    while (temp > 0)
    {
        digits++;
        temp /= 10;
    }
    ptr = s + digits - 1; // Last digit position

    // Write digits in reverse order
    while (n > 0)
    {
        *ptr-- = (n % 10) + '0'; // Write digit
        n /= 10;
    }

    // Null-terminate
    *(s + digits) = '\0';

    return start;
}
