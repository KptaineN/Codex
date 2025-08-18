/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiefer <nkiefer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 15:37:36 by nkiefer           #+#    #+#             */
/*   Updated: 2025/08/16 15:40:34 by nkiefer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPLIT_H
# define SPLIT_H

#include "minishell.h"

typedef struct s_scan_ctx
{
        const char      *str;
        t_shell         *shell;
        int             i;
        int             count;
        bool            in_sq;
        bool            in_dq;
        bool            in_word;
}       t_scan_ctx;

void    toggle_quotes_ctx(t_scan_ctx *s);
void    flush_on_space_ctx(t_scan_ctx *s);
void    handle_oper_or_word_ctx(t_scan_ctx *s);
void    handle_count_char_ctx(t_scan_ctx *s);

int     count_arg(const char *str, t_shell *shell);
char    *extract_arg(const char *str, int *start, t_shell *shell);
t_arr   *custom_split(const char *str, t_shell *shell);
int     skip_spaces(const char *s, int pos);

#endif // SPLIT_H

