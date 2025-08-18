/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiefer <nkiefer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 16:35:29 by eganassi          #+#    #+#             */
/*   Updated: 2025/08/13 22:30:42 by nkiefer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

static int	count_exportable(const t_list *env)
{
	int			count;
	const t_env	*e;

	count = 0;
	while (env)
	{
		e = (const t_env *)env->content;
		if (e && e->value)
			count++;
		env = env->next;
	}
	return (count);
}

/* Construit une nouvelle chaîne "key=value" (malloc) */
static char	*make_kv_cstr(const char *k, const char *v)
{
	size_t	nk;
	size_t	nv;
	char	*s;

	if (!k || !v)
		return (NULL);
	nk = ft_strlen(k);
	nv = ft_strlen(v);
	s = (char *)malloc(nk + 1 + nv + 1);
	if (!s)
		return (NULL);
	ft_memcpy(s, k, nk);
	s[nk] = '=';
	ft_memcpy(s + nk + 1, v, nv);
	s[nk + 1 + nv] = '\0';
	return (s);
}

/* Libère un envp partiellement rempli (filled éléments) */
static void	free_envp_partial(char **envp, int filled)
{
	int	i;

	i = filled - 1;
	while (i >= 0)
		free(envp[i--]);
	free(envp);
}

/* Convertit la liste env -> tableau envp (NULL-terminé) */
char	**list_to_envp(t_list *env)
{
	int			n;
	int			i;
	char		**envp;
	const t_env	*cur;

	n = count_exportable(env);
	envp = (char **)malloc(sizeof(char *) * (n + 1));
	if (!envp)
		return (NULL);
	i = 0;
	while (env)
	{
		cur = (const t_env *)env->content;
		if (cur && cur->value)
		{
			envp[i] = make_kv_cstr(cur->key, cur->value);
			if (!envp[i])
				return (free_envp_partial(envp, i), NULL);
			i++;
		}
		env = env->next;
	}
	envp[i] = NULL;
	return (envp);
}
