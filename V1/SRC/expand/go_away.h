/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   go_away.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiefer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 12:46:02 by nkiefer           #+#    #+#             */
/*   Updated: 2025/08/16 12:46:04 by nkiefer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GO_AWAY_H
# define GO_AWAY_H

# include "../../include/minishell.h"

typedef struct s_ctx
{
	bool		in_sq;
	bool		in_dq;
	size_t		i;
	size_t		j;
}				t_stx;

typedef struct s_rep
{
	const char	*code;
	size_t		clen;
}				t_rep;

int				try_quote(const char *s, t_stx *c, char *out);
int				try_exit(const char *s, t_stx *c, char *out, t_rep *r);
char			*expand_input(char *input, t_shell *sh);
void			ctx_init(t_stx *c);
char			*fill_with_replacement(const char *input, const char *code_str,
					size_t out_len);
char			*replace_exit_code(const char *input, int code);
size_t			count_exit_patterns(const char *s);
size_t			compute_out_len(size_t input_len, size_t count,
					size_t code_len);
void			update_quotes(bool *in_sq, bool *in_dq, char c);

#endif
