/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiefer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 22:30:48 by nkiefer           #+#    #+#             */
/*   Updated: 2025/08/13 22:30:53 by nkiefer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

void	free_env_list(t_list *lst)
{
	t_list	*next;
	t_env	*e;

	while (lst)
	{
		next = lst->next;
		e = (t_env *)lst->content;
		if (e)
		{
			free(e->key);
			free(e->value);
			free(e);
		}
		free(lst);
		lst = next;
	}
}

int	env_len(t_list *env)
{
	int	count;

	count = 0;
	while (env)
	{
		count++;
		env = env->next;
	}
	return (count);
}

void	print_env(t_list *env)
{
	t_env	*cur;

	while (env)
	{
		cur = env->content;
		if (cur->value)
			printf("%s=%s\n", cur->key, cur->value);
		else
			printf("%s=\n", cur->key);
		env = env->next;
	}
}
