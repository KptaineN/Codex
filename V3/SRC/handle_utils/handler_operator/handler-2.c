#include "../../../include/minishell.h"


int handle_pipe(t_shell *shell, char **argv)
{
    (void) shell;
    (void) argv; // Suppress unused parameter warning
    printf("Handling PIPE (|)\n");
    // TODO: Implement pipe logic
    return 0;
}
int handle_redirect_in(t_shell *shell, char **argv)
{
    (void) shell;
    (void) argv; // Suppress unused parameter warning
    printf("Handling REDIRECT_IN (<)\n");
    // TODO: Implement input redirection logic
    return 0;
}
int handle_redirect_out(t_shell *shell, char **argv)
{
    (void) shell;
    (void) argv; // Suppress unused parameter warning
    printf("Handling REDIRECT_OUT (>)\n");
    // TODO: Implement output redirection logic
    return 0;

}