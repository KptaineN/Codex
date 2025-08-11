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

/*
 * Build a linked list of command tokens from the array of tokens
 * produced during parsing. Only command or builtin tokens are kept
 * and the resulting list is stored in shell->cmd_head.
 */
void build_cmd_list(t_shell *shell)
{
    t_token *prev;
    int     i;

    if (!shell || !shell->tokens)
        return ;
    shell->cmd_head = NULL;
    shell->cmd_tail = NULL;
    shell->n_cmd = 0;
    prev = NULL;
    i = 0;
    while (i < shell->n_tokens)
    {
        t_token *tok = &shell->tokens[i];
        if (tok->type == TOKEN_CMD || tok->type == TOKEN_BCMD)
        {
            if (prev)
                prev->next = tok;
            tok->next = NULL;
            add_cmd(shell, tok);
            prev = tok;
            shell->n_cmd++;
        }
        i++;
    }
}

int count_args_cmd(t_shell *shell, int i)
{
    int     n_args;
    char    **arr;
    int     len;
    int     idx_oper;
    char    *op;

    if (!shell || !shell->parsed_args || !shell->parsed_args->arr)
        return 0;
    arr = (char **)shell->parsed_args->arr;
    len = shell->parsed_args->len;
    n_args = 0;
    while (i < len && arr[i])
    {
        idx_oper = is_in_t_arr_dic_str(shell->oper, arr[i]);
        if (idx_oper != -1)
        {
            if (idx_oper < 2 || idx_oper > 4)
            {
                op = ((t_dic *)shell->oper->arr[idx_oper])->key;
                if ((int)ft_strlen(arr[i]) == (int)ft_strlen(op))
                    i++;
                i++;
                continue;
            }
            break;
        }
        n_args++;
        i++;
    }
    if (n_args == 0)
        return 1;
    return n_args;
}


static char *strip_quotes(const char *s)
{
    size_t len;

    if (!s)
        return NULL;
    len = ft_strlen(s);
    if (len >= 2 && ((s[0] == '"' && s[len - 1] == '"') || (s[0] == '\'' && s[len - 1] == '\'')))
        return ft_substr(s, 1, len - 2);
    return ft_strdup(s);
}

int file_access_redirection(t_shell *shell, void **arr, int t_arr_index, int i)
{
    char    *token;
    char    *op;
    char    *fname;
    char    *clean;
    int     consumed;
    int     fd;

    token = (char *)arr[i];
    op = ((t_dic *)shell->oper->arr[t_arr_index])->key;
    consumed = 1;
    if ((int)ft_strlen(token) > (int)ft_strlen(op))
        fname = token + ft_strlen(op);
    else
    {
        fname = (char *)arr[i + 1];
        consumed = 2;
    }
    clean = strip_quotes(fname);
    if (!clean)
        return consumed;
    if (t_arr_index == 5)
    {
        fd = open(clean, O_RDONLY);
        if (fd < 0)
            perror(clean);
        else
        {
            if (shell->fd_in != STDIN_FILENO && shell->fd_in != -1)
                close(shell->fd_in);
            shell->fd_in = fd;
        }
    }
    else if (t_arr_index == 6)
    {
        fd = open(clean, O_CREAT | O_WRONLY | O_TRUNC, 0644);
        if (fd < 0)
            perror(clean);
        else
        {
            if (shell->fd_out != STDOUT_FILENO && shell->fd_out != -1)
                close(shell->fd_out);
            shell->fd_out = fd;
        }
    }
    else if (t_arr_index == 1)
    {
        fd = open(clean, O_CREAT | O_WRONLY | O_APPEND, 0644);
        if (fd < 0)
            perror(clean);
        else
        {
            if (shell->fd_out != STDOUT_FILENO && shell->fd_out != -1)
                close(shell->fd_out);
            shell->fd_out = fd;
        }
    }
    else if (t_arr_index == 0)
    {
        char *argv[3];
        argv[0] = NULL;
        argv[1] = clean;
        argv[2] = NULL;
        handle_heredoc(shell, argv);
        clean = NULL; /* already used by heredoc */
    }
    free(clean);
    return consumed;
}

