/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiefer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 01:23:04 by nkiefer           #+#    #+#             */
/*   Updated: 2025/08/18 01:23:06 by nkiefer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "minishell.h"

void	assign_redirs(t_shell *sh);
char	*op_key(t_shell *sh, int op_idx);
int		is_redir_op(int op_idx);
int		report_missing_fname(t_shell *sh);
int		file_access_redirection(t_shell *shell, void **arr, int t_arr_index,
			int i);
char	*extract_fname(t_shell *sh, char **arr, int *i, int op_idx);
void	push_redir_if_current(t_token *cur, int op_idx, char *fname);
bool	escape_check(const char *str, int idx);
int		find_c_nonescaped(const char *str, char *needle, int size_needle);

#endif // LEXER_H
