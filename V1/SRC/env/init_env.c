/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiefer <nkiefer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 22:30:59 by nkiefer           #+#    #+#             */
/*   Updated: 2025/08/13 22:33:37 by nkiefer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

static int	parse_entry(const char *s, char **out_key, char **out_val)
{
	char	*eq;

	*out_key = NULL;
	*out_val = NULL;
	if (!s)
		return (-1);
	eq = ft_strchr(s, '=');
	if (!eq)
		return (0);
	*out_key = ft_substr(s, 0, eq - s);
	*out_val = ft_strdup(eq + 1);
	if (!*out_key || !*out_val)
	{
		free(*out_key);
		free(*out_val);
		*out_key = NULL;
		*out_val = NULL;
		return (-1);
	}
	return (1);
}

static t_list	*new_env_node_take(char *key, char *value)
{
	t_env	*env;
	t_list	*node;

	env = (t_env *)malloc(sizeof(*env));
	node = (t_list *)malloc(sizeof(*node));
	if (!env || !node)
	{
		free(key);
		free(value);
		free(env);
		free(node);
		return (NULL);
	}
	env->key = key;
	env->value = value;
	node->content = env;
	node->next = NULL;
	return (node);
}

static void	append_node(t_list **head, t_list **tail, t_list *node)
{
	if (!*head)
		*head = node;
	else
		(*tail)->next = node;
	*tail = node;
}

static int	add_env_entry(const char *s, t_list **head, t_list **tail)
{
	char	*key;
	char	*val;
	int		st;
	t_list	*node;

	key = NULL;
	val = NULL;
	st = parse_entry(s, &key, &val);
	if (st <= 0)
		return (st);
	node = new_env_node_take(key, val);
	if (!node)
		return (-1);
	append_node(head, tail, node);
	return (1);
}

t_list	*init_env(char **envp)
{
	t_list	*head;
	t_list	*tail;
	int		i;
	int		r;

	head = NULL;
	tail = NULL;
	i = 0;
	while (envp && envp[i])
	{
		r = add_env_entry(envp[i], &head, &tail);
		if (r < 0)
			return (free_env_list(head), NULL);
		i++;
	}
	return (head);
}
