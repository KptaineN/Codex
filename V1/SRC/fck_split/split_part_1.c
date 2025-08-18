/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_part_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiefer <nkiefer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 15:25:28 by nkiefer           #+#    #+#             */
/*   Updated: 2025/08/16 15:38:47 by nkiefer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "split.h"

/* =============================
 * Découpe la chaîne en tokens
 * ============================= */
int	allocate_t_arr_for_split(t_arr **out, const char *str, t_shell *shell)
{
	t_arr	*res;
	int		argc;

	if (!str)
		return (-1);
	res = malloc(sizeof(t_arr));
	if (!res)
		return (-1);
	argc = count_arg(str, shell);
	if (argc <= 0)
	{
		free(res);
		return (-1);
	}
	res->len = argc;
	res->arr = malloc(sizeof(char *) * (argc + 1));
	if (!res->arr)
	{
		free(res);
		return (-1);
	}
	*out = res;
	return (0);
}

void	free_split_partial(t_arr *res, int upto)
{
	int		i;
	char	**arr;

	if (!res)
		return ;
	arr = (char **)res->arr;
	i = 0;
	while (arr && i < upto)
	{
		free(arr[i]);
		i++;
	}
	free(res->arr);
	free(res);
}

int	fill_tokens(const char *str, t_shell *shell, t_arr *res)
{
	int		pos;
	int		k;
	char	**arr;

	pos = 0;
	k = 0;
	arr = (char **)res->arr;
	while (k < res->len)
	{
		arr[k] = extract_arg(str, &pos, shell);
		if (!arr[k])
		{
			free_split_partial(res, k);
			return (-1);
		}
		k++;
	}
	arr[res->len] = NULL;
	return (0);
}

t_arr	*custom_split(const char *str, t_shell *shell)
{
	t_arr	*result;

	result = NULL;
	if (allocate_t_arr_for_split(&result, str, shell) < 0)
		return (NULL);
	if (fill_tokens(str, shell, result) < 0)
		return (NULL);
	return (result);
}

int	skip_spaces(const char *s, int pos)
{
	while (s[pos] && s[pos] == ' ')
		pos++;
	return (pos);
}
