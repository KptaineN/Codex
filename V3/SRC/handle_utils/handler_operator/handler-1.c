#include "../../../include/minishell.h"


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

int handle_append(t_shell *shell, char **argv)
{
    int     fd;
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
    fd = open(path, O_CREAT | O_APPEND | O_WRONLY, 0644);
    if (fd < 0)
    {
        perror(path);
        free(path);
        return (1);
    }
    if (shell->fd_out != STDOUT_FILENO && shell->fd_out != -1)
        close(shell->fd_out);
    shell->fd_out = fd;
    ret = 0;
    free(path);
    return (ret);
}

int handle_and(t_shell *shell, char **argv)
{
    (void) shell;
    (void) argv; // Suppress unused parameter warning
    printf("Handling AND (&&)\n");
    // TODO: Implement logical AND logic
    return 0;
}

int handle_or(t_shell *shell, char **argv)
{
    (void) shell;
    (void) argv; // Suppress unused parameter warning
    printf("Handling OR (||)\n");
    // TODO: Implement logical OR logic
    return 0;
}