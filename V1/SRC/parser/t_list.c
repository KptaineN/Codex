/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_list.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiefer <nkiefer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 15:01:38 by eganassi          #+#    #+#             */
/*   Updated: 2025/08/16 14:24:14 by nkiefer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*new;

	new = malloc(sizeof(t_list));
	if (!new)
		return (NULL);
	new->content = content;
	new->next = NULL;
	return (new);
}

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*tmp;

	if (!lst || !new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	tmp = *lst;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

void	push_lst(t_list **tail, void *content)
{
	t_list	*new;

	if (!*tail)
		return ;
	new = malloc(sizeof(t_list));
	if (!new)
		perror("MALLOC push_list");
	(*tail)->next = new;
	(*tail) = (*tail)->next;
	new->content = content;
	new->next = NULL;
}
/**
t_list	*set_linked_path(char **env)
{
	t_list	*head;
	t_list	*node;
	int		i;

	i = 0;
	head = NULL;
	while (env[i])
	{
		node = ft_lstnew(strdup(env[i]));
		if (!node)
			return (NULL);
		ft_lstadd_back(&head, node);
		i++;
	}
	return (head);
}

void	ft_lstadd_front(t_list **lst, void *content)
{
	t_list	*new_node;

	if (!lst || !content)
		return ;
	new_node = malloc(sizeof(t_list));
	if (!new_node)
		return ;
	new_node->content = ft_strdup((char *)content);
	if (!new_node->content)
	{
		free(new_node);
		return ;
	}
	new_node->next = *lst;
	*lst = new_node;
}

t_list	*search_lst(t_list *lst, const char *target)
{
	size_t	target_len;
	char	*s;

	if (!lst || !target)
		return (NULL);
	target_len = ft_strlen(target);
	while (lst)
	{
		s = (char *)lst->content;
		(void)s;
		if (lst->content && ft_strncmp((char *)lst->content, target,
				target_len) == 0)
			return (lst);
		lst = lst->next;
	}
	return (NULL);
}


void	replace_or_add(t_list **lst, const char *old, const char *new)
{
	t_list *node;

	if (!*lst || !old || !new)
		return ;
	node = search_lst(*lst, old);
	if (node)
	{
		free(node->content);
		node->content = ft_strdup(new);
		if (!node->content)
			node->content = NULL;
		return ;
	}
	ft_lstadd_front(lst, (void *)new);
}*/
