/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_args.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiefer <nkiefer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 15:55:45 by nkiefer           #+#    #+#             */
/*   Updated: 2025/08/13 16:07:56 by nkiefer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "export.h"

int	is_valid_identifier(const char *name)
{
	int	i;

	i = 0;
	if (!name || !*name)
		return (0);
	if (!ft_isalpha(*name) && *name != '_')
		return (0);
	i = 1;
	while (name[i])
	{
		if (!ft_isalnum(name[i]) && name[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

int	handle_arg_with_assignment(char *arg, t_shell *shell)
{
	char	*eq;
	int		ret;

	eq = ft_strchr(arg, '=');
	ret = 0;
	*eq = '\0';
	if (!is_valid_identifier(arg))
	{
		fprintf(stderr, "minishell: export: `%s': not a valid identifier\n",
			arg);
		shell->exit_status = 1;
		ret = 1;
	}
	else if (set_env_var(shell, arg, eq + 1) != 0)
		ret = 1;
	*eq = '=';
	return (ret);
}

int	handle_arg_without_assignment(char *arg, t_shell *shell)
{
	if (!is_valid_identifier(arg))
	{
		fprintf(stderr, "minishell: export: `%s': not a valid identifier\n",
			arg);
		shell->exit_status = 1;
		return (1);
	}
	if (!find_env_var(shell, arg))
		return (set_env_var(shell, arg, NULL));
	return (0);
}

int	process_export_argument(char *arg, t_shell *shell)
{
	if (ft_strchr(arg, '='))
		return (handle_arg_with_assignment(arg, shell));
	return (handle_arg_without_assignment(arg, shell));
}

int	export_no_arguments(t_shell *shell)
{
	char	**arr;

        arr = env_to_array(shell);
        if (!arr)
        {
                shell->exit_status = 1;
                return (1);
        }
        ft_bubble_str_sort(arr);
        print_export_arr(arr);
        free_export_arr(arr);
        shell->exit_status = 0;
        return (0);
}
