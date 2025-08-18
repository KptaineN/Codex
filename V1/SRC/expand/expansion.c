/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiefer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 12:45:20 by nkiefer           #+#    #+#             */
/*   Updated: 2025/08/16 12:45:24 by nkiefer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "go_away.h"

size_t	compute_out_len(size_t input_len, size_t count, size_t code_len)
{
	size_t	pattern_len;

	pattern_len = 2;
	if (count == 0)
		return (input_len);
	return (input_len + count * (code_len - pattern_len));
}

size_t	count_exit_patterns(const char *s)
{
	t_stx	c;
	bool	handled;

	if (!s)
		return (0);
	ctx_init(&c);
	while (s[c.i])
	{
		handled = false;
		if (try_quote(s, &c, NULL))
			handled = true;
		if (!handled && try_exit(s, &c, NULL, NULL))
			handled = true;
		if (!handled)
			c.i++;
	}
	return (c.j);
}

char	*replace_exit_code(const char *input, int code)
{
	char	*code_str;
	size_t	code_len;
	size_t	count;
	size_t	out_len;
	char	*res;

	code_len = 0;
	count = 0;
	out_len = 0;
	if (!input)
		return (NULL);
	code_str = ft_itoa(code);
	if (!code_str)
		return (NULL);
	code_len = ft_strlen(code_str);
	count = count_exit_patterns(input);
	out_len = compute_out_len(ft_strlen(input), count, code_len);
	res = fill_with_replacement(input, code_str, out_len);
	free(code_str);
	return (res);
}

char	*expand_status(char *input, t_shell *sh)
{
	char	*res;

	res = replace_exit_code(input, sh->exit_status);
	return (res);
}

char	*expand_input(char *input, t_shell *sh)
{
	char	*s1;
	char	*s2;

	s1 = expand_status(input, sh);
	if (!s1)
		return (NULL);
	s2 = replace_variables(s1, sh);
	free(s1);
	return (s2);
}
