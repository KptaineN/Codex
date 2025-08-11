/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_list.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiefer <nkiefer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 15:01:38 by eganassi          #+#    #+#             */
/*   Updated: 2025/08/07 14:16:37 by nkiefer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"


t_list	*ft_lstnew(void *content)
{
	t_list	*new;

	new = malloc(sizeof(t_list));
	if (!new)
    {
        perror("MALLOC in ft_lstnew");
		return (NULL);
    }
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

//gives to the next
void	push_lst(t_list **tail, void *content)
{
	t_list *new;

	if (!*tail)
		return ;
	new = malloc(sizeof(t_list));
	if (!new)
    {
		perror("MALLOC push_list");   
		return ;
	}
	(*tail)->next = new;
	(*tail) = (*tail)->next; 
	new->content = content;
	new->next = NULL;
}

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
/*
static int count_linked(t_list *node)
{
	int count = 1;
	t_list *first = node;
	if (!node)
		return 0;
	node = node->next;
	while (node != first)
	{
		count++;
		node = node->next ; 
	}
	return count;
}*/
/**
char **linked_to_array_string(t_list *node)
{
	t_list *first = node;
	int len = count_linked(node);
	char **arr = malloc(sizeof(char *)*(len+1));
	arr[len] = 0;
	int i = 0;

	while(i<len)
	{
		arr[i] = node->content;
		node = node->next;
		i++;
	}
	node = first;
	return arr;
}*/
/*char **linked_to_array_string(t_list *env)
{
    int len = 0;
    t_list *tmp = env;
    while (tmp) { len++; tmp = tmp->next; }
    char **arr = malloc(sizeof(char *) * (len + 1));
    tmp = env;
    for (int i = 0; i < len; i++) {
        arr[i] = tmp->content;
        tmp = tmp->next;
    }
    arr[len] = NULL;
    return arr;
}*/
char **linked_to_array_string(t_list *node)
{
    int len = 0;
    t_list *tmp = node;
    while (tmp) { len++; tmp = tmp->next; }
    char **arr = malloc(sizeof(char *) * (len + 1));
    int i = 0;
    tmp = node;
    while (tmp)
    {
        arr[i++] = ft_strdup(tmp->content);
        tmp = tmp->next;
    }
    arr[i] = NULL;
    return arr;
}


void ft_lstadd_front(t_list **lst, void *content)
{
    t_list *new_node;

    if (!lst || !content)
        return;

    // Allocate new node
    new_node = malloc(sizeof(t_list));
    if (!new_node)
        return; // Allocation failure

    // Duplicate content (assumes char *)
    new_node->content = strdup((char *)content);
    if (!new_node->content)
    {
        free(new_node);
        return; // Allocation failure
    }

    // Link new node to current head
    new_node->next = *lst;
    *lst = new_node; // Update head to new node
}

t_list *search_lst(t_list *lst, const char *target)
{
    size_t target_len;

    if (!lst || !target)
        return NULL;

    target_len = strlen(target);

    while (lst)
    {
        char *s  = (char *)lst->content;
        (void)s;
        if (lst->content && strncmp((char *)lst->content, target, target_len) == 0)
            return lst;
        lst = lst->next;
    }

    return NULL;
}


void replace_or_add(t_list **lst, const char *old, const char *new)
{
    t_list *node;

    if (!*lst || !old || !new)
        return;

    // Search for node matching old
    node = search_lst(*lst, old);
    if (node)
    {
        // Match found: free old content and replace
        free(node->content);
        node->content = strdup(new);
        if (!node->content)
        {
            // Handle strdup failure (optional: remove node or set to NULL)
            node->content = NULL;
        }
        return;
    }

    // No match: add new node at front
    ft_lstadd_front(lst, (void *)new);
}