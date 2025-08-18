/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiefer <nkiefer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 16:34:25 by nkiefer           #+#    #+#             */
/*   Updated: 2025/08/16 16:53:00 by nkiefer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../launch/launcher.h"

t_list	*find_env_entry(t_list *env, const char *key)
{
	size_t	key_len;
	char	*entry;

	if (!env || !key)
		return (NULL);
	key_len = ft_strlen(key);
	while (env)
	{
		entry = (char *)env->content;
		if (entry && ft_strncmp(entry, key, key_len) == 0
			&& entry[key_len] == '=')
			return (env);
		env = env->next;
	}
	return (NULL);
}

char	*build_kv_string(const char *key, const char *value)
{
	size_t	k;
	size_t	v;
	char	*s;

	if (!key)
		return (NULL);
	k = ft_strlen(key);
	if (value)
		v = ft_strlen(value);
	else
	{
		v = 0;
	}
	s = (char *)malloc(k + 1 + v + 1);
	if (!s)
		return (NULL);
	ft_memcpy(s, key, k);
	s[k] = '=';
	if (v)
		ft_memcpy(s + k + 1, value, v);
	s[k + 1 + v] = '\0';
	return (s);
}

static int	replace_env_if_exists(t_list *env, const char *key,
		const char *value)
{
	t_list	*cur;
	char	*s;
	size_t	klen;

	klen = ft_strlen(key);
	cur = env;
	while (cur)
	{
		if (cur->content && ft_strncmp((char *)cur->content, key, klen) == 0
			&& ((char *)cur->content)[klen] == '=')
		{
			if (value)
				s = build_kv_string(key, value);
			else
				s = build_kv_string(key, "");
			if (!s)
				return (-1);
			free(cur->content);
			cur->content = s;
			return (1);
		}
		cur = cur->next;
	}
	return (0);
}

void	replace_or_add_env(t_list **env, const char *key, const char *value)
{
	int		ret;
	char	*s;
	t_list	*node;

	if (!env || !key)
		return ;
	ret = replace_env_if_exists(*env, key, value);
	if (ret != 0)
		return ;
	if (value)
		s = build_kv_string(key, value);
	else
		s = build_kv_string(key, "");
	if (!s)
		return ;
	node = ft_lstnew(s);
	if (!node)
	{
		free(s);
		return ;
	}
	ft_lstadd_back(env, node);
}
