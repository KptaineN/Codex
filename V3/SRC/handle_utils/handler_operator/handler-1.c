#include "../../../include/minishell.h"


/*int handle_heredoc(t_shell *shell, char **argv)
{
    (void) shell;
    (void) argv; // Suppress unused parameter warning
    printf("Handling HEREDOC (<<)\n");
    // TODO: Implement heredoc logic
    return 0;
}*/

int handle_append(t_shell *shell, char **argv)
{
    int fd;

    if (!argv || !argv[1])
    {
        ft_putendl_fd("minishell: syntax error near unexpected token `newline'",
            STDERR_FILENO);
        return (1);
    }
    fd = open(argv[1], O_CREAT | O_APPEND | O_WRONLY, 0644);
    if (fd < 0)
    {
        perror(argv[1]);
        return (1);
    }
    if (shell->fd_out != STDOUT_FILENO && shell->fd_out != -1)
        close(shell->fd_out);
    shell->fd_out = fd;
    return (0);
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