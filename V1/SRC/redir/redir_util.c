/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiefer <nkiefer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 02:24:48 by nkiefer           #+#    #+#             */
/*   Updated: 2025/08/18 02:27:40 by nkiefer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redir.h"

void    ambiguous(const char *original)
{
        ft_putstr_fd((char *)"minishell: ", STDERR_FILENO);
        ft_putstr_fd((char *)original, STDERR_FILENO);
        ft_putstr_fd((char *)": ambiguous redirect\n", STDERR_FILENO);
}

int     is_ambiguous(const char *fname, const char *raw)
{
        size_t  i;

        if (!fname || *fname == '\0')
                return (1);
        if (ft_strchr(raw, '\'') || ft_strchr(raw, '"'))
                return (0);
        i = 0;
        while (fname[i])
        {
                if (fname[i] == ' ')
                        return (1);
                i++;
        }
        return (0);
}
