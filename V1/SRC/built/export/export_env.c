/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiefer <nkiefer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 15:55:54 by nkiefer           #+#    #+#             */
/*   Updated: 2025/08/13 16:08:45 by nkiefer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "export.h"

t_list	*find_env_var(t_shell *shell, const char *key)
{
	t_env	*env;
	t_list	*node;

	node = shell->env;
	while (node)
	{
		env = (t_env *)node->content;
		if (ft_strcmp(env->key, key) == 0)
			return (node);
		node = node->next;
	}
	return (NULL);
}

int	update_env_var(t_list *env_node, const char *value)
{
	t_env	*env;

	env = (t_env *)env_node->content;
	free(env->value);
	if (value != NULL)
		env->value = ft_strdup(value);
	else
		env->value = NULL;
	return (0);
}

int	create_env_var(t_shell *shell, const char *key, const char *value)
{
	t_env	*new_env;
	t_list	*new_node;

	new_env = malloc(sizeof(*new_env));
	if (new_env == NULL)
		return (1);
	new_env->key = ft_strdup(key);
	if (value != NULL)
		new_env->value = ft_strdup(value);
	else
		new_env->value = NULL;
	new_node = malloc(sizeof(*new_node));
	if (new_node == NULL)
	{
		free(new_env->key);
		free(new_env->value);
		free(new_env);
		return (1);
	}
	new_node->content = new_env;
	new_node->next = shell->env;
	shell->env = new_node;
	return (0);
}

int	set_env_var(t_shell *shell, const char *key, const char *value)
{
	t_list	*existing;

	existing = find_env_var(shell, key);
	if (existing)
		return (update_env_var(existing, value));
	else
		return (create_env_var(shell, key, value));
}
