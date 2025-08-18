/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiefer <nkiefer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 16:24:10 by eganassi          #+#    #+#             */
/*   Updated: 2025/08/18 02:30:48 by nkiefer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*read_user_input(void)
{
	char	*input;

	input = readline("ᕕ( ᐛ )ᕗ minishell$ ");
	if (!input)
		write(1, "exit\n", 5);
	return (input);
}

int	looping(t_shell *shell)
{
	char	*in;
	int		r;

	while (1)
	{
		in = read_user_input();
		if (!in)
			break ;
		r = process_input(shell, in);
		if (r == 1)
			break ;
	}
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;

	if (argc != 1 || argv[1])
	{
		ft_putstr_fd("Usage: ./minishell\n", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	print_header_emote();
	if (!start_shell(&shell, envp))
	{
		ft_putstr_fd("Failed to start minishell\n", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	looping(&shell);
	free_minishell(&shell);
	return (shell.exit_status);
}
