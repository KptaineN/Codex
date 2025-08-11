#include "../../../include/minishell.h"


int handle_pipe(t_shell *shell, char **argv)
{
    (void)shell;
    (void)argv;
    printf("Handling PIPE (|)\n");
    return (0);
}

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