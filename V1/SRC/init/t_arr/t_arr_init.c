/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_arr_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiefer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 14:21:22 by nkiefer           #+#    #+#             */
/*   Updated: 2025/08/16 14:21:24 by nkiefer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	init_oper_t_arr(t_shell *shell)
{
	char	*all_operators[7];
	int		(*operator_handlers[7])(t_shell *, char **);
	int		n_operateurs;

	all_operators[0] = "<<";
	all_operators[1] = ">>";
	all_operators[2] = "&&";
	all_operators[3] = "||";
	all_operators[4] = "|";
	all_operators[5] = "<";
	all_operators[6] = ">";
	operator_handlers[0] = handle_heredoc;
	operator_handlers[1] = handle_append;
	operator_handlers[2] = handle_and;
	operator_handlers[3] = handle_or;
	operator_handlers[4] = handle_pipe;
	operator_handlers[5] = handle_redirect_in;
	operator_handlers[6] = handle_redirect_out;
	n_operateurs = 7;
	build_t_arr_dic_str(&shell->oper, all_operators, operator_handlers,
		n_operateurs);
}

void	init_builtins_t_arr(t_shell *shell)
{
	char	*all_builtins[7];
	int		(*builtin_handlers[7])(t_shell *, char **);
	int		n_builtins;

	all_builtins[0] = "echo";
	all_builtins[1] = "cd";
	all_builtins[2] = "pwd";
	all_builtins[3] = "export";
	all_builtins[4] = "unset";
	all_builtins[5] = "env";
	all_builtins[6] = "exit";
	builtin_handlers[0] = ft_echo;
	builtin_handlers[1] = ft_cd;
	builtin_handlers[2] = ft_pwd;
	builtin_handlers[3] = ft_export;
	builtin_handlers[4] = ft_unset;
	builtin_handlers[5] = ft_env;
	builtin_handlers[6] = ft_exit;
	n_builtins = 7;
	build_t_arr_dic_str(&shell->bcmd, all_builtins, builtin_handlers,
		n_builtins);
}

void	init_all_t_arr(t_shell *shell)
{
	init_oper_t_arr(shell);
	init_builtins_t_arr(shell);
}
