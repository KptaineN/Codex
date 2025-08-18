/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_exp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiefer <nkiefer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 15:05:35 by nkiefer           #+#    #+#             */
/*   Updated: 2025/08/16 15:07:56 by nkiefer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	append_literal(const char *src, int len, char *dst, int *pi)
{
	int	i;

	i = 0;
	while (i < len)
	{
		dst[*pi + i] = src[i];
		i++;
	}
	*pi += len;
}

void	append_from_head_and_pop(t_list **phead, char *dst, int *pi)
{
	t_list	*tmp;
	char	*str;
	size_t	len;

	if (!phead || !*phead)
		return ;
	str = (char *)(*phead)->content;
	len = ft_strlen(str);
	ft_strcpy(&dst[*pi], str);
	*pi += len;
	tmp = *phead;
	*phead = (*phead)->next;
	free(tmp->content);
	free(tmp);
}

int	advance_after_dollar(t_subtoken *b, int k)
{
	int	idx;

	idx = k;
	if (idx + 1 < b->len && b->p[idx + 1] == '$')
		idx++;
	else
		idx += count_exp_len(b, &idx);
	return (idx);
}

void	process_unquoted_subtoken(t_subtoken *b, char *dst, int *pi,
		t_list **phead)
{
	int	k;
	int	i;

	k = 0;
	i = *pi;
	while (k < b->len)
	{
		if (b->p[k] == '$')
		{
			append_from_head_and_pop(phead, dst, &i);
			k = advance_after_dollar(b, k);
		}
		else
		{
			dst[i] = b->p[k];
			i++;
		}
		k++;
	}
	*pi = i;
}

char	*build_expansion(t_subtoken_container *a, int count, t_list **add_head)
{
	t_list	*head;
	char	*new;
	int		i;
	int		j;

	head = *add_head;
	new = malloc(count + 1);
	if (!new)
	{
		perror("MALLOC build_expansion");
		return (NULL);
	}
	i = 0;
	j = 0;
	while (j < a->n_parts)
	{
		if (a->parts[j].type == QUOTE_SINGLE)
			append_literal(a->parts[j].p, a->parts[j].len, new, &i);
		else
			process_unquoted_subtoken(&a->parts[j], new, &i, &head);
		j++;
	}
	new[i] = '\0';
	*add_head = head;
	return (new);
}
