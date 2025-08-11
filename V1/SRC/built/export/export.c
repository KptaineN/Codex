#include "export.h"

int builtin_export(t_shell *shell, char **argv)
{
    int error;
    int i;

    if (!argv[1])
        return export_no_arguments(shell);
    error = 0;
    i = 1;
    while (argv[i])
    {
        error |= process_export_argument(argv[i], shell);
        i++;
    }
    shell->exit_status = error;
    return error;
}
