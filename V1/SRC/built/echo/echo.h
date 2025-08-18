/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiefer <nkiefer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 15:35:07 by nkiefer           #+#    #+#             */
/*   Updated: 2025/08/13 21:55:11 by nkiefer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ECHO_H
# define ECHO_H

# include "../../../include/minishell.h"

int		builtin_echo(t_shell *shell, char **argv);
char	*get_dollar_value(const char *arg, int *pos, t_shell *sh);
char	*replace_variables(const char *arg, t_shell *sh);
int		is_valid_key_char(char c);
int		process_dollar(char *dst, const char *arg, int *i, t_shell *sh);
int		dollar_edge_cases(char *dst, const char *arg, int *i, t_shell *sh);
char	*remove_quotes(const char *arg);
int		is_echo_n_flag(const char *s);
char	*find_env_value(t_list *env, const char *key);
int		write_and_free(char *dst, char *s, int *i, int new_i);
void	toggle_quotes(char c, bool *in_sq, bool *in_dq);

#endif