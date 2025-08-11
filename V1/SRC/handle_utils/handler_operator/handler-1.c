#include "../../../include/minishell.h"

int handle_and(t_shell *shell, char **argv)
{
    (void)shell;
    (void)argv;
    printf("Handling AND (&&)\n");
    return (0);
}

int handle_or(t_shell *shell, char **argv)
{
    (void)shell;
    (void)argv;
    printf("Handling OR (||)\n");
    return (0);
}
