/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_util.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiefer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 15:19:25 by nkiefer           #+#    #+#             */
/*   Updated: 2025/08/16 15:19:27 by nkiefer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int	count_exp_len(t_subtoken *b, int *k)
{
	int	var_len;

	var_len = 0;
	if (ft_isalpha(b->p[*k + 1]) || b->p[*k + 1] == '_')
	{
		var_len = 1;
		while (*k + 1 + var_len < b->len && (ft_isalnum(b->p[*k + 1 + var_len])
				|| b->p[*k + 1 + var_len] == '_'))
			var_len++;
	}
	return (var_len);
}

int	sum_parts_len(t_subtoken_container *a)
{
	int	total;
	int	idx;

	total = 0;
	idx = 0;
	while (idx < a->n_parts)
	{
		total += a->parts[idx].len;
		idx++;
	}
	return (total);
}
/*
void	expand_variable(t_subtoken *b, int *k, t_list **curr, int *count,
		t_list *env)
{
	int		var_len;
	char	*value;

	var_len = count_exp_len(b, k);
	if (var_len > 0)
	{
		value = get_value_env(env, (char *)&b->p[(*k) + 1], var_len);
		push_lst(curr, ft_strdup_count(value, count));
		*k += var_len;
	}
}

void	expand_str(t_subtoken *b, t_list *env, int *count, t_list **curr)
{
	int k = 0;
	while (k < b->len)
	{
		if (k < b->len && b->p[k] == '$')
		{
			if (k + 1 == b->len || b->p[k + 1] == ' ')
				push_lst(curr, ft_strdup_count("$", count));
			else if (b->p[k + 1] == '$')
			{
				push_lst(curr, ft_strdup(get_value_env(env, "PID", 3)));
				k++;
			}
			else
				expand_variable(b, &k, curr, count, env);
		}
		else
			(*count)++;
		k++;
	}
}*/
