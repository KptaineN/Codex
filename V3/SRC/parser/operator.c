#include "../../include/minishell.h"

// "<<",">>","&&","||","|","<",">"
//   0    1   2     3   4   5   6
void file_access_redirection(t_shell *shell, int t_arr_index, int i)
{
    char **argv;

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
