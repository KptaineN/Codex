/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiefer <nkiefer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 22:20:55 by eganassi          #+#    #+#             */
/*   Updated: 2025/08/11 13:51:30 by nkiefer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"



void add_cmd(t_shell *shell, t_token *token)
{
    t_list *tmp = malloc(sizeof(t_list));
    if (!tmp)
    {
        perror("Erreur malloc add_cmd");
        return;
    }

    tmp->content = (void *)token;
    tmp->next = NULL;

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
}

int count_args_cmd(t_shell *shell, int i)
{
    int n_args = 0;
    char **arr;
    int len;
    int idx_oper;

    if (!shell || !shell->parsed_args || !shell->parsed_args->arr)
        return 0;

    arr = (char **)shell->parsed_args->arr;
    len = shell->parsed_args->len;

    while (i < len && arr[i] != NULL)
    {
        //printf("count_args_cmd: arr[%d] = \"%s\"\n", i, arr[i]);

        // Vérifie si on tombe sur un opérateur (|, <, >, etc.)
        idx_oper = is_in_t_arr_dic_str(shell->oper, arr[i]);
        if (idx_oper != -1)
        {
            // On s'arrête avant l'opérateur
            return n_args;
        }

        n_args++;
        i++;
    }

    if (n_args == 0)
    {
        //printf("count_args_cmd: No valid arguments found.\n");
        return 1; // Par défaut, on considère 1 argument (au moins la commande elle-même)
    }
    return n_args;
}


void file_access_redirection(t_shell *shell, void **arr, int t_arr_index, int i)
{
	if (i + 1 >= shell->n_tokens)
		perror("Argument manquant pour l'opérateur");

	if (t_arr_index == 5)
	{
		if (shell->fd_in != -1)
		{
			shell->fd_in = open(arr[i + 1], O_RDONLY);
			if (shell->fd_in < 0)
				perror("Erreur lors de l'ouverture en lecture");
		}
		else if (access(arr[i + 1], O_RDONLY) < 0)
		{
			perror("ERROR ACCESS");
		}
		return;
	}

	// sortie 
	if (shell->fd_out != -1)
	{
		if (t_arr_index == 1)
		{
			shell->fd_out = open(arr[i + 1], O_CREAT | O_RDWR | O_APPEND, 0644);
			if (shell->fd_out < 0)
				perror("Erreur lors de l'ouverture en écriture (append)");
		}
		else if (t_arr_index == 6)
		{
			shell->fd_out = open(arr[i + 1], O_CREAT | O_RDWR, 0644);
			if (shell->fd_out < 0)
				perror("Erreur lors de l'ouverture en écriture (trunc)");
		}
		return;
	}

	if (t_arr_index == 1)
	{
		if (access(arr[i + 1], O_CREAT | O_RDWR | O_APPEND | O_TRUNC) < 0)
			perror("Erreur lors de l'ouverture en écriture (append)");
	}
	else if (t_arr_index == 6)
	{
		if (access(arr[i + 1], O_CREAT | O_RDWR | O_TRUNC) < 0)
			perror("Erreur lors de l'ouverture en écriture (trunc)");
	}
}