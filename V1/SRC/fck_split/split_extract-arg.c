/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_extract-arg.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiefer <nkiefer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 15:25:20 by nkiefer           #+#    #+#             */
/*   Updated: 2025/08/16 15:38:12 by nkiefer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "split.h"

/* =============================
 * Extrait un argument (token)
 * ============================= */

int	operator_len_at(const char *s, int pos, t_shell *shell)
{
	int		idx;
	t_dic	*dic;
	int		len;

	idx = is_in_t_arr_dic_str(shell->oper, (char *)&s[pos]);
	if (idx == -1)
		return (0);
	dic = (t_dic *)shell->oper->arr[idx];
	len = ft_strlen((char *)dic->key);
	return (len);
}

void	update_quotes(const char *s, int i, bool *in_sq, bool *in_dq)
{
	if (s[i] == '\'' && !*in_dq && escape_check(s, i))
		*in_sq = !*in_sq;
	else if (s[i] == '"' && !*in_sq && escape_check(s, i))
		*in_dq = !*in_dq;
}

int	scan_token_end(const char *s, int pos, t_shell *shell)
{
	int		i;
	bool	in_sq;
	bool	in_dq;

	i = pos;
	in_sq = false;
	in_dq = false;
	while (s[i])
	{
		update_quotes(s, i, &in_sq, &in_dq);
		if (!in_sq && !in_dq)
		{
			if (s[i] == ' ')
				break ;
			if (operator_len_at(s, i, shell) > 0)
				break ;
		}
		i++;
	}
	return (i);
}

char	*dup_slice(const char *s, int start, int end)
{
	int		len;
	char	*out;

	len = end - start;
	out = malloc(len + 1);
	if (!out)
		return (NULL);
	ft_memcpy(out, s + start, len);
	out[len] = '\0';
	return (out);
}

char	*extract_arg(const char *str, int *start, t_shell *shell)
{
	int		token_start;
	int		token_end;
	int		oplen;
	char	*token;

	token_start = *start;
	token_end = 0;
	oplen = 0;
	token = NULL;
	token_start = skip_spaces(str, token_start);
	if (!str[token_start])
		return (NULL);
	oplen = operator_len_at(str, token_start, shell);
	if (oplen > 0)
	{
		token = dup_slice(str, token_start, token_start + oplen);
		if (!token)
			return (NULL);
		*start = token_start + oplen;
		return (token);
	}
	token_end = scan_token_end(str, token_start, shell);
	*start = token_end;
	token = dup_slice(str, token_start, token_end);
	return (token);
}
