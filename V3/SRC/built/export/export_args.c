#include "export.h"

int is_valid_identifier(const char *name)
{
    if (!name || !*name)
        return 0;
    if (!ft_isalpha(*name) && *name != '_')
        return 0;
    for (int i = 1; name[i]; i++)
    {
        if (!ft_isalnum(name[i]) && name[i] != '_')
            return 0;
    }
    return 1;
}

int handle_arg_with_assignment(char *arg, t_shell *shell)
{
    char *eq = ft_strchr(arg, '=');
    int ret = 0;

    *eq = '\0';
    if (!is_valid_identifier(arg))
    {
        printf("minishell: export: `%s': not a valid identifier\n", arg);
        ret = 1;
    }
    else if (set_env_var(shell, arg, eq + 1) != 0)
        ret = 1;
    *eq = '=';

    return ret;
}

int handle_arg_without_assignment(char *arg, t_shell *shell)
{
    if (!is_valid_identifier(arg))
    {
        printf("minishell: export: `%s': not a valid identifier\n", arg);
        return 1;
    }
    if (!find_env_var(shell, arg))
        return set_env_var(shell, arg, NULL);
    return 0;
}

int process_export_argument(char *arg, t_shell *shell)
{
    if (ft_strchr(arg, '='))
        return handle_arg_with_assignment(arg, shell);
    return handle_arg_without_assignment(arg, shell);
}
