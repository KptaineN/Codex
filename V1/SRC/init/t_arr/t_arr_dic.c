/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_arr_dic.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiefer <nkiefer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 22:08:28 by eganassi          #+#    #+#             */
/*   Updated: 2025/08/16 14:21:53 by nkiefer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* ************************************************************************** */
/*                        t_arr <key:string, value:fn>                        */
/* ************************************************************************** */

static void	free_dic_partial(t_arr **dst, int upto)
{
	int		j;
	t_dic	*d;

	if (!dst || !*dst || !(*dst)->arr)
		return ;
	j = 0;
	while (j < upto)
	{
		d = (t_dic *)(*dst)->arr[j];
		if (d)
		{
			free(d->key);
			free(d);
		}
		j++;
	}
	free((*dst)->arr);
	free(*dst);
	*dst = NULL;
}

static int	alloc_t_arr(t_arr **dst, int len)
{
	*dst = malloc(sizeof(t_arr));
	if (!*dst)
		return (-1);
	(*dst)->len = len;
	(*dst)->arr = malloc(sizeof(t_dic *) * len);
	if (!(*dst)->arr)
	{
		free(*dst);
		*dst = NULL;
		return (-1);
	}
	return (0);
}

static int	make_dic_entry(t_dic **out, const char *key, int (*fn)(t_shell *,
			char **))
{
	t_dic	*dic;
	char	*dup;

	dic = malloc(sizeof(t_dic));
	if (!dic)
		return (-1);
	dup = ft_strdup(key);
	if (!dup)
	{
		free(dic);
		return (-1);
	}
	dic->key = dup;
	dic->value = (void *)fn;
	*out = dic;
	return (0);
}

void	build_t_arr_dic_str(t_arr **dst, char **keys, int (**values)(t_shell *,
			char **), int len)
{
	int		i;
	t_dic	*dic;

	if (alloc_t_arr(dst, len) < 0)
		return ;
	i = 0;
	while (i < len)
	{
		dic = NULL;
		if (make_dic_entry(&dic, keys[i], values[i]) < 0)
			return (free_dic_partial(dst, i));
		(*dst)->arr[i] = dic;
		i++;
	}
}
