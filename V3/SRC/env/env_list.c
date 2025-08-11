/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiefer <nkiefer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 16:35:29 by eganassi          #+#    #+#             */
/*   Updated: 2025/07/14 18:28:31 by nkiefer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

#include <stdlib.h>

int env_len(t_list *env)
{
	int count = 0;

	while (env)
	{
		count++;
		env = env->next;
	}
	return count;
}

/*
char	**env_to_envp(t_env *env)
{
    t_env	*curr;
    int		count = 0;
    char	**envp;
    int		i;

    curr = env;
    while (curr)
    {
        count++;
        curr = curr->next;
    }
    envp = malloc(sizeof(char *) * (count + 1));
    if (!envp)
        handle_error("malloc");
    i = 0;
    curr = env;
    while (curr)
    {
        envp[i] = ft_strjoin_3(curr->key, "=", curr->value);
        i++;
        curr = curr->next;
    }
    envp[i] = NULL;
    return (envp);
}*/

// parse la string "KEY=VALUE" en t_env
// Dans ton create_env (ou équivalent) :
/*
t_env	*create_env(char *env_str)
{
	t_env	*node;
	char	*equal;
	size_t	key_len;

	node = malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	equal = ft_strchr(env_str, '=');
	if (!equal)
	{
		free(node);
		return (NULL);
	}
	key_len = equal - env_str;
	node->key = malloc(key_len + 1);
	if (!node->key)
	{
		free(node);
		return (NULL);
	}
	if (ft_strlcpy(node->key, env_str, key_len + 1) != key_len)
		handle_error("ft_strlcpy error copying key");
	node->value = ft_strdup(equal + 1);
	node->next = NULL;
	return (node);
}*//*
t_env	*create_env(const char *key, const char *value)
{
	t_env	*node;

	node = malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	node->key = ft_strdup(key);
	if (!node->key)
	{
		free(node);
		return (NULL);
	}
	node->value = ft_strdup(value);
	if (!node->value)
	{
		free(node->key);
		free(node);
		return (NULL);
	}
	node->next = NULL;
	return (node);
}

char **env_to_envp(t_env *env)
{
    int count = env_len(env);
    char **envp = malloc(sizeof(char *) * (count + 1));
    t_env *curr = env;
    int i = 0;
    if (!envp)
        return NULL;
    while (curr)
    {
        int keylen = ft_strlen(curr->key);
        int vallen = ft_strlen(curr->value);
        envp[i] = malloc(keylen + 1 + vallen + 1); // key + '=' + value + '\0'
        if (!envp[i])
        {
            // clean up before return !
            for (int j = 0; j < i; ++j) free(envp[j]);
            free(envp);
            return NULL;
        }
        ft_strcpy(envp[i], curr->key);
        envp[i][keylen] = '=';
        ft_strcpy(envp[i] + keylen + 1, curr->value);
        i++;
        curr = curr->next;
    }
    envp[i] = NULL;
    return envp;
}*/

void print_env(t_list *env)
{
    while (env)
    {
        printf("%s\n", (char*)env->content);
        env = env->next;
    }
}


t_list *init_env(char **envp)
{
    t_list *head = NULL, *new = NULL;
    int i = 0;

    while (envp[i])
    {
        new = malloc(sizeof(t_list));
        if (!new)
            return NULL;
        new->content = strdup(envp[i]);   // Copie "KEY=VALUE"
        new->next = NULL;
        if (!head)
            head = new;
        else
        {
            t_list *tmp = head;
            while (tmp->next)
                tmp = tmp->next;
            tmp->next = new;
        }
        i++;
    }
    return head;
}
