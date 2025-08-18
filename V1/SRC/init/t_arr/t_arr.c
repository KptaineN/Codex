/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_arr.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiefer <nkiefer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 14:03:34 by nkiefer           #+#    #+#             */
/*   Updated: 2025/08/16 14:17:30 by nkiefer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	t_arrlen(void **arr)
{
	size_t	len;

	len = 0;
	if (!arr)
		return (0);
	while (arr[len])
		len++;
	return (len);
}

int	is_in_t_arr_str(t_arr *arr, const char *arg)
{
	int		i;
	int		found;
	int		valid;
	t_dic	*dic;

	if (!arr || !arr->arr || !arg)
		return (-1);
	i = 0;
	found = -1;
	while (i < arr->len && found == -1)
	{
		dic = (t_dic *)arr->arr[i];
		valid = (dic && dic->key);
		if (valid && ft_strcmp(dic->key, arg) == 0)
			found = i;
		if (found == -1)
			i++;
	}
	return (found);
}

int	is_in_t_arr_dic_str(t_arr *arr, const char *arg)
{
	int		i;
	t_dic	*dic;
	size_t	len_key;

	if (!arr || !arr->arr || !arg)
		return (-1);
	i = 0;
	while (i < arr->len)
	{
		dic = (t_dic *)arr->arr[i];
		if (!dic || !dic->key)
		{
			i++;
			continue ;
		}
		len_key = ft_strlen(dic->key);
		if (ft_strncmp(dic->key, arg, len_key) == 0)
			return (i);
		i++;
	}
	return (-1);
}

void	build_t_arr_str(t_arr **dst, char **arr_str, int len)
{
	int	i;

	*dst = malloc(sizeof(t_arr));
	if (!*dst)
		return ;
	(*dst)->len = len;
	(*dst)->arr = malloc(sizeof(char *) * len);
	if (!(*dst)->arr)
	{
		free(*dst);
		*dst = NULL;
		return ;
	}
	i = 0;
	while (i < len)
	{
		(*dst)->arr[i] = ft_strdup(arr_str[i]);
		if (!(*dst)->arr[i])
		{
			free(*dst);
			*dst = NULL;
			return ;
		}
		i++;
	}
}
