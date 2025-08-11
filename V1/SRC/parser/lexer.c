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


void file_access_redirection(t_shell *shell, int t_arr_index, int i)
{
    char    **argv;

    if (!shell || !shell->parsed_args || i < 0)
        return;
    argv = (char **)&shell->parsed_args->arr[i];
    if (t_arr_index == 0)
        handle_heredoc(shell, argv);
    else if (t_arr_index == 1)
        handle_append(shell, argv);
    else if (t_arr_index == 5)
        handle_redirect_in(shell, argv);
    else if (t_arr_index == 6)
        handle_redirect_out(shell, argv);
}