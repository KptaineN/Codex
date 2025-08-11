/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiefer <nkiefer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 22:20:55 by eganassi          #+#    #+#             */
/*   Updated: 2025/08/07 17:12:40 by nkiefer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int count_args_cmd(t_shell *shell, int i)
{
	int n_args = 0;
	char **arr = (char **)shell->parsed_args->arr;
	int len = shell->parsed_args->len;
	
        int idx_oper;
        while (1)
        {
                if (i==len)
                        break;
                if (arr[i] != NULL)
                {
                        idx_oper = is_in_t_arr_dic_str(shell->oper, arr[i]);
                        if (idx_oper != -1)
                                return n_args;
                        n_args++;
                }
                i++;
        }
	return n_args;
}

void subtoken_of_cmd(t_subtoken_container *container, char *arg)
{
	t_subtoken *parts;
	char *head = arg;
	int idx_tail;
	int n_parts = container->n_parts;
	container->parts = malloc(sizeof(t_subtoken)*n_parts);
	parts = container->parts;
	if (!parts)
		return;

	int i = 0;
	int idx = 0;
	while(head[idx])
	{
		if (head[idx] == '\'' && escape_check(head,idx))
		{	
			idx++;
			parts[i].type = QUOTE_SINGLE;
			idx_tail = find_c_nonescaped(&head[idx],"\'", 1);
		}
		else if (head[idx] == '\"' && escape_check(head,idx))
		{	
			idx++;
			parts[i].type = QUOTE_DOUBLE;
			idx_tail = find_c_nonescaped(&head[idx],"\"", 1);
		}
		else
		{	
			parts[i].type = QUOTE_NONE;
			idx_tail = find_c_nonescaped(&head[idx],"\"\'",2);
		}
                parts[i].len = idx_tail;
                parts[i].p = (char *)&head[idx];
                idx+= idx_tail+(parts[i].type != QUOTE_NONE);
		//if (parts[i].type != QUOTE_NONE)
		//	head+=2;
		i++;
	}
}



int attribute_cmd_subtokens(t_shell *shell, t_token *cmd_token, int idx, int len)
{
	t_subtoken_container *arr_container;
	t_arr *arr_arg = shell->parsed_args;
	char *curr_arg;
	int idx_container = 0;
	cmd_token->cmd_args_parts = malloc(sizeof(t_subtoken_container *)*len);
	arr_container = cmd_token->cmd_args_parts;
	if (!arr_container)
		return -1;

	while(idx_container<len)
	{
		curr_arg = arr_arg->arr[idx];
		if (curr_arg != NULL)
		{
			arr_container[idx_container].n_parts = count_subtokens(curr_arg);
			subtoken_of_cmd(&arr_container[idx_container++], curr_arg);
		}
		idx++;
	}
	cmd_token->n_parts = len;
	return idx-1;
}


static void add_cmd(t_shell *shell, t_token *token)
{
	t_list *tmp;
 	tmp = malloc(sizeof(t_list));
	if (!tmp)
			return; // ERROR
	
	
	if (!shell->cmd_head)
	{	
		shell->cmd_head = tmp;
		shell->cmd_tail = tmp;
	}
	else
	{
		shell->cmd_tail->next = tmp;
		shell->cmd_tail = tmp;
	}
	tmp->content = (void *)token;
	tmp->next = NULL;
}


void attribute_token_type(t_shell *shell)
{
 	int t_arr_index;
    int i = 0;
	int idx_token = 0;
	void **arr = shell->parsed_args->arr;
	t_token *token;
	
	shell->n_tokens = count_tokens(shell);
	if (shell->n_tokens != 0)
	{
		shell->tokens = malloc(sizeof(t_token)*shell->n_tokens);
		if (!shell->tokens)
			perror("Erreur d'allocation pour les tokens");
	}
	while(idx_token < shell->n_tokens)
	{
		if (arr[i] != NULL)
		{
			token = &shell->tokens[idx_token];
			token->type = TOKEN_WORD;
			token->value = arr[i];
			
                        // OPERATOR: les <> << >> sont deja geres par count_tokens; pour le bonus, il faudrait subdiviser le parse pour decouper les tokens
			t_arr_index = is_in_t_arr_dic_str(shell->oper, arr[i]);
			if (t_arr_index != -1)
				token->type = TOKEN_OPER;
			//BCMD 
			if (token->type == TOKEN_WORD)
			{
				t_arr_index = is_in_t_arr_dic_str(shell->bcmd, arr[i]);
				if (t_arr_index != -1)
					token->type = TOKEN_BCMD;
				else
					token->type = TOKEN_CMD;
				int n_args = count_args_cmd(shell, i);
    			i = attribute_cmd_subtokens(shell, token, i, n_args);
			}
			if (token->type != TOKEN_OPER)
			{	
				add_cmd(shell,token);
				shell->n_cmd++;
			}
			i++;
		}
		idx_token++;
	}
	shell->cmd_tail = shell->cmd_head;
}
