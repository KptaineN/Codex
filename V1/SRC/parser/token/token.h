/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiefer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 01:19:01 by nkiefer           #+#    #+#             */
/*   Updated: 2025/08/18 01:19:06 by nkiefer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

# include "../../../include/minishell.h"

typedef struct s_qstate
{
	bool		in_sq;
	bool		in_dq;
	bool		in_nq;
	int			count;
}				t_qstate;

typedef struct s_it
{
	int			idx;
	int			k;
}				t_it;

typedef struct s_stctx
{
	const char	*arg;
	int			arg_len;
	int			idx;
	int			i;
	t_subtoken	*parts;
}				t_stctx;

int				count_subtokens(const char *str);
void			subtoken_of_cmd(t_subtoken_container *container, char *arg);
int				attribute_cmd_subtokens(t_shell *shell, t_token *cmd_token,
					int idx, int len);
void			subtoken_of_cmd(t_subtoken_container *container, char *arg);
void			token_set_value_or_die(t_token *tok, char **args, int i);
int				is_operator_here(t_shell *sh, char **args, int i);
int				process_operator_token(t_token *tok, int i);
int				advance_after_operator(t_shell *sh, t_arr *parsed_args, int i,
					int op_idx);
int				advance_after_command(t_shell *sh, int i);

#endif // TOKEN_H
