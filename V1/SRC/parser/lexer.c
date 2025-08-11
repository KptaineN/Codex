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
    int     consumed;

    (void)shell;
    token = (char *)arr[i];
    op = ((t_dic *)shell->oper->arr[t_arr_index])->key;
    consumed = 1;
    if ((int)ft_strlen(token) == (int)ft_strlen(op))
        consumed = 2;
    return consumed;
}

static void add_redir(t_token *tok, t_rtype type, const char *arg)
{
    t_redir *new_r;

    new_r = realloc(tok->r, sizeof(t_redir) * (tok->r_count + 1));
    if (!new_r)
        return;
    tok->r = new_r;
    tok->r[tok->r_count].type = type;
    tok->r[tok->r_count].arg = strip_quotes(arg);
    tok->r_count++;
}

void assign_redirs(t_shell *shell)
{
    if (!shell || !shell->parsed_args || !shell->parsed_args->arr)
        return;

    char    **arr = (char **)shell->parsed_args->arr;
    t_token *current = NULL;
    int      cmd_idx = 0;

    for (int i = 0; i < shell->parsed_args->len; )
    {
        int op_idx = is_in_t_arr_dic_str(shell->oper, arr[i]);
        if (op_idx == -1)
        {
            if (!current && cmd_idx < shell->n_tokens)
            {
                current = &shell->tokens[cmd_idx++];
            }
            i++;
        }
        else if (op_idx < 2 || op_idx > 4)
        {
            char *op = ((t_dic *)shell->oper->arr[op_idx])->key;
            char *fname;
            if ((int)ft_strlen(arr[i]) > (int)ft_strlen(op))
            {
                fname = arr[i] + ft_strlen(op);
                i++;
            }
            else
            {
                fname = arr[i + 1];
                i += 2;
            }
            if (!fname || *fname == '\0')
            {
                ft_putstr_fd((char *)"minishell: missing file name for redirection\n", STDERR_FILENO);
                shell->exit_status = 1;
                shell->n_tokens = 0;
                return;
            }
            int fd = -1;
            if (op_idx == 5)
                fd = open(fname, O_RDONLY);
            else if (op_idx == 6)
                fd = open(fname, O_CREAT | O_WRONLY | O_TRUNC, 0644);
            else if (op_idx == 1)
                fd = open(fname, O_CREAT | O_WRONLY | O_APPEND, 0644);
            if (fd < 0 && op_idx != 0)
            {
                perror(fname);
                shell->exit_status = 1;
                shell->n_tokens = 0;
                return;
            }
            if (fd >= 0)
                close(fd);
            if (current)
            {
                if (op_idx == 5)
                    add_redir(current, R_IN, fname);
                else if (op_idx == 6)
                    add_redir(current, R_OUT_TRUNC, fname);
                else if (op_idx == 1)
                    add_redir(current, R_OUT_APPEND, fname);
                else if (op_idx == 0)
                    add_redir(current, R_HEREDOC, fname);
            }
        }
        else
        {
            current = NULL;
            i++;
        }
    }
}

