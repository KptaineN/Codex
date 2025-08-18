/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiefer <nkiefer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 02:24:32 by nkiefer           #+#    #+#             */
/*   Updated: 2025/08/18 02:30:13 by nkiefer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIR_H
# define REDIR_H

# include "../../include/minishell.h"

int		build_heredoc_fd(t_delim d, t_shell *sh);
int		apply_redirs_in_child(t_cmd *c, t_shell *sh);
void	ambiguous(const char *original);
int		is_ambiguous(const char *fname);
char	*expand_filename_if_needed(char *arg, t_shell *sh);
int		run_builtin(t_cmd *c, t_shell *sh);
char	*resolve_path(const char *cmd, t_shell *sh);
//void	child_exec_maillon(t_cmd *c, t_shell *sh, int i, int ncmd, int p[][2]);
char	*replace_exit_code(const char *arg, int exit_status);
char	*replace_variables(const char *arg, t_shell *sh);
int		open_and_dup_in(char *raw, t_shell *sh);
int		open_and_dup_out_trunc(char *raw, t_shell *sh);
int		open_and_dup_out_append(char *raw, t_shell *sh);
int		handle_heredoc_child(char *raw, t_shell *sh);
int		open_from_expansion(char *raw, t_shell *sh, int flags, int mode);
t_delim	parse_delim(const char *raw);
int		handle_heredoc(t_shell *shell, char **argv);

#endif // !REDIR_H
