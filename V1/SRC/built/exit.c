/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiefer <nkiefer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 15:26:26 by nkiefer           #+#    #+#             */
/*   Updated: 2025/08/16 13:56:40 by nkiefer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_shell(t_shell *shell, int exit_code)
{
	free_minishell(shell);
	rl_clear_history();
	exit(exit_code);
}

int	is_numeric(const char *str)
{
	int	i;

	i = 0;
	if (!str || !str[0])
		return (0);
	if (str[0] == '+' || str[0] == '-')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	builtin_exit(t_shell *shell, char **argv)
{
	long	code;

	code = 0;
	write(1, "exit\n", 5);
	if (argv[1])
	{
		if (!is_numeric(argv[1]))
		{
			ft_putstr_fd("┐(￣ ヘ￣)┌minishell: exit: numeric argument required\n",
				2);
			exit_shell(shell, 2);
		}
		if (argv[2])
		{
			ft_putstr_fd("╮(╯ _╰ )╭minishell: exit: too many arguments\n", 2);
			return (1);
		}
		code = ft_atoi(argv[1]);
		exit_shell(shell, code % 256);
	}
	exit_shell(shell, 0);
	return (0);
}
