/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ChatGPT <chatgpt@example.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 00:00:00 by ChatGPT           #+#    #+#             */
/*   Updated: 2025/10/15 00:00:00 by ChatGPT          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int  open_infile(t_shell *shell, const char *path)
{
    int fd;

    fd = open(path, O_RDONLY);
    if (fd < 0)
    {
        perror(path);
        return (1);
    }
    if (shell->fd_in != STDIN_FILENO && shell->fd_in != -1)
        close(shell->fd_in);
    shell->fd_in = fd;
    return (0);
}

static int  open_outfile(t_shell *shell, const char *path, int flags)
{
    int fd;

    fd = open(path, flags, 0644);
    if (fd < 0)
    {
        perror(path);
        return (1);
    }
    if (shell->fd_out != STDOUT_FILENO && shell->fd_out != -1)
        close(shell->fd_out);
    shell->fd_out = fd;
    return (0);
}

int handle_redirect_in(t_shell *shell, char **argv)
{
    char    *path;
    int     ret;

    if (!argv || !argv[1])
    {
        ft_putendl_fd("minishell: syntax error near unexpected token `newline'",
            STDERR_FILENO);
        return (1);
    }
    path = remove_quotes(argv[1]);
    if (!path)
        return (1);
    ret = open_infile(shell, path);
    free(path);
    return (ret);
}

int handle_redirect_out(t_shell *shell, char **argv)
{
    char    *path;
    int     ret;

    if (!argv || !argv[1])
    {
        ft_putendl_fd("minishell: syntax error near unexpected token `newline'",
            STDERR_FILENO);
        return (1);
    }
    path = remove_quotes(argv[1]);
    if (!path)
        return (1);
    ret = open_outfile(shell, path, O_CREAT | O_TRUNC | O_WRONLY);
    free(path);
    return (ret);
}

int handle_append(t_shell *shell, char **argv)
{
    char    *path;
    int     ret;

    if (!argv || !argv[1])
    {
        ft_putendl_fd("minishell: syntax error near unexpected token `newline'",
            STDERR_FILENO);
        return (1);
    }
    path = remove_quotes(argv[1]);
    if (!path)
        return (1);
    ret = open_outfile(shell, path, O_CREAT | O_APPEND | O_WRONLY);
    free(path);
    return (ret);
}

int handle_heredoc(t_shell *shell, char **argv)
{
    int     fd;
    char    *line;
    char    *limiter;

    if (!argv || !argv[1])
    {
        ft_putendl_fd("minishell: syntax error near unexpected token `newline'",
            STDERR_FILENO);
        return (1);
    }
    limiter = argv[1];
    fd = open(".heredoc_tmp", O_CREAT | O_WRONLY | O_TRUNC, 0600);
    if (fd < 0)
    {
        perror("heredoc");
        return (1);
    }
    while (1)
    {
        write(STDOUT_FILENO, "> ", 2);
        line = get_next_line(STDIN_FILENO);
        if (!line)
            break;
        size_t len = ft_strlen(line);
        if (len > 0 && line[len - 1] == '\n')
            line[len - 1] = '\0';
        if (ft_strcmp(line, limiter) == 0)
        {
            free(line);
            break;
        }
        write(fd, line, ft_strlen(line));
        write(fd, "\n", 1);
        free(line);
    }
    close(fd);
    fd = open(".heredoc_tmp", O_RDONLY);
    if (fd < 0)
    {
        perror("heredoc");
        return (1);
    }
    if (shell->fd_in != STDIN_FILENO && shell->fd_in != -1)
        close(shell->fd_in);
    shell->fd_in = fd;
    unlink(".heredoc_tmp");
    return (0);
}

