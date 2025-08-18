/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiefer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 16:09:23 by nkiefer           #+#    #+#             */
/*   Updated: 2025/08/13 16:09:30 by nkiefer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPORT_H
# define EXPORT_H

# include "../../../include/minishell.h"

// Au début de ton header (ex : echo.h ou export.h)
int		builtin_export(t_shell *shell, char **argv);

int		export_no_arguments(t_shell *shell);
int		process_export_argument(char *arg, t_shell *shell);
// --- export_utils.c ---
size_t	env_count(t_shell *shell);
char	**env_to_array(t_shell *shell);
void	print_export_arr(char **arr);
void	free_export_arr(char **arr);
int		export_no_arguments(t_shell *shell);

// --- export_args.c ---
int		is_valid_identifier(const char *name);
int		handle_arg_with_assignment(char *arg, t_shell *shell);
int		handle_arg_without_assignment(char *arg, t_shell *shell);
int		process_export_argument(char *arg, t_shell *shell);

// --- export_env.c ---
t_list	*find_env_var(t_shell *shell, const char *key);
int		update_env_var(t_list *env, const char *value);
int		create_env_var(t_shell *shell, const char *key, const char *value);
int		set_env_var(t_shell *shell, const char *key, const char *value);
char	*create_env_entry(t_env *env);

#endif
