/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_value.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiefer <nkiefer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 15:34:48 by nkiefer           #+#    #+#             */
/*   Updated: 2025/08/13 15:49:56 by nkiefer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "echo.h"

char	*find_env_value(t_list *env, const char *key)
{
	t_env	*entry;

	while (env)
	{
		entry = env->content;
		if (ft_strcmp(entry->key, key) == 0)
			return (entry->value);
		env = env->next;
	}
	return (NULL);
}

static char	*get_special_var(const char *key)
{
	if (ft_strncmp(key, "NRICO", ft_strlen("NRICO") + 1) == 0)
		return (ft_strdup("le 2 eme meilleur dev de la galaxie 🚀"));
	if (ft_strncmp(key, "NOE", ft_strlen("NOE") + 1) == 0)
		return (ft_strdup("le meilleur dev de la galaxie 🚀"));
	return (NULL);
}

static char	*extract_key(const char *arg, int start, int *len)
{
	int	i;

	i = 0;
	while (is_valid_key_char(arg[start + i]))
		i++;
	*len = i;
	if (i == 0)
		return (NULL);
	return (ft_substr(arg, start, i));
}

static char	*get_env_or_special_value(t_shell *shell, const char *key)
{
	const char	*val_env = find_env_value(shell->env, key);
	char		*sp;

	if (val_env)
		return (ft_strdup(val_env));
	sp = get_special_var(key);
	if (sp)
		return (sp);
	return (ft_strdup(""));
}

char	*get_dollar_value(const char *arg, int *pos, t_shell *sh)
{
	int		k;
	char	*key;
	char	*val;
	int		len;

	k = *pos + 1;
	if (arg[k] == '?')
	{
		val = ft_itoa(sh->exit_status);
		*pos = k + 1;
		return (val);
	}
	key = extract_key(arg, k, &len);
	if (!key)
	{
		*pos = k;
		return (NULL);
	}
	val = get_env_or_special_value(sh, key);
	free(key);
	*pos = k + len;
	return (val);
}
// attention a :
//              88_________*pos = k;