/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiefer <nkiefer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 16:24:10 by eganassi          #+#    #+#             */
/*   Updated: 2025/08/07 17:31:15 by nkiefer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
/*
static const char	**get_left(void)
{
	static const char *left[] = 
    {
    "                                                                             ",
    "      ███▄ ▄███▓ ██▓ ███▄    █  ██▓  ██████  ██░ ██ ▓█████  ██▓     ██▓      ",
	"     ▓██▒▀█▀ ██▒▓██▒ ██ ▀█   █ ▓██▒▒██    ▒ ▓██░ ██▒▓█   ▀ ▓██▒    ▓██▒      ",
	"     ▓██    ▓██░▒██▒▓██  ▀█ ██▒▒██▒░ ▓██▄   ▒██▀▀██░▒███   ▒██░    ▒██░      ",
	"     ▒██    ▒██ ░██░▓██▒  ▐▌██▒░██░  ▒   ██▒░▓█ ░██ ▒▓█  ▄ ▒██░    ▒██░      ",
	"     ▒██▒   ░██▒░██░▒██░   ▓██░░██░▒██████▒▒░▓█▒░██▓░▒████▒░██████▒░██████▒  ",
	"     ░ ▒░   ░  ░░▓  ░ ▒░   ▒ ▒ ░▓  ▒ ▒▓▒ ▒ ░ ▒ ░░▒░▒░░ ▒░ ░░ ▒░▓  ░░ ▒░▓  ░  ",
	"      ░  ░      ░ ▒ ░░ ░░   ░ ▒░ ▒ ░░ ░▒  ░ ░ ▒ ░▒░ ░ ░ ░  ░░ ░ ▒  ░░ ░ ▒  ░ ",
	"      ░      ░    ▒ ░   ░   ░ ░  ▒ ░░  ░  ░   ░  ░░ ░   ░     ░ ░     ░ ░    ",
	"           ░    ░           ░  ░        ░   ░  ░  ░   ░  ░    ░  ░    ░  ░   ",
	"                                                                             ",
	"          )))         ╔╗╔┌─┐┌─┐   ┬   ╔═╗┌┐┌┬─┐┬┌─┐┌─┐          (((          ",
	"         (o o)        ║║║│ │├┤   ┌┼─  ║╣ │││├┬┘││  │ │         (o o)         ",
	"        --(_)--       ╝╚╝└─┘└─┘  └┘   ╚═╝┘└┘┴└─┴└─┘└─┘        --(_)--        ",
	NULL
    };
	return (left);
}

static void	print_right(int i)
{
	char	*right[] = {"⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⡠⠤⠖⢒⠂⢤⣀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀",
			"⠀⢀⣀⠀⠀⠀⠀⠀⢠⠖⠁⠀⠀⠀⠀⠀⠀⠢⣥⣢⠀⠀⠀⠀⠀⣠⣤⠀", "⢀⣟⣿⣦⠀⠀⠀⣰⡿⠿⠷⠶⣄⠀⠀⢠⠾⠟⠛⠛⢷⡀⠀⢀⡼⣿⣇⡇",
			"⠈⠛⠛⠿⢕⡂⢴⠁⠀⠀⠀⢀⠈⠆⠠⣮⣴⢤⡀⣀⣸⣗⣶⡧⠒⠉⠉⠁", "⠀⠀⠀⠀⠀⢹⠀⠀⠴⣺⣿⣿⠇⠀⠀⠛⡿⣽⣿⣽⠿⠛⢻⠀⠀⠀⠀⠀",
			"⠀⠀⠀⠀⠀⡌⠀⠀⠈⠉⢩⠀⠀⠀⠀⠀⣸⣒⣄⠀⠀⠀⠀⠇⠀⠀⠀⠀", "⠀⠀⠀⠀⠀⡇⠀⢀⡴⠖⠉⠛⠓⠲⠶⠾⠿⠿⠿⢏⡳⡀⠄⣾⠀⠀⠀⠀",
			"⠀⠀⠀⠀⠀⠃⠀⠞⠀⣀⣀⣀⣀⣀⣀⣀⣤⣤⣶⣿⣇⢧⠀⣿⠀⠀⠀⠀", "⠀⠀⠀⠀⠀⡄⠀⠀⠀⠈⠫⢽⣽⣉⣹⣁⣧⣿⠟⣱⣿⣾⢀⣿⠀⠀⠀⠀",
			"⠀⠀⠀⠀⠀⢃⠀⠀⠀⠀⠀⠀⠉⠙⠩⠤⠭⣶⣋⡟⢸⢁⣿⠏⠀⠀⠀⠀", "⠀⠀⠀⠀⠀⠀⠱⡀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠛⠝⡇⣘⡾⠋⠀⠀⠀⠀⠀",
			"⠀⠀⠀⠀⠀⠀⠀⠈⠢⣀⠀⠀⠀⠀⠀⠀⠀⣠⣴⣷⠋⠀⠀⠀⠀⠀⠀⠀", "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠑⠠⠤⠤⠤⠤⠾⠟⠋⠁⠀⠀⠀⠀⠀⠀⠀⠀",
			NULL};

	if (right[i])
		ft_putstr_fd(right[i], 1);
}

static void	print_startup_emote(void)
{
	const char	**left = get_left();
	int			i;

	ft_putstr_fd("\033[40m\033[32m", 1);
	i = 0;
	while (left[i])
	{
		ft_putstr_fd((char *)left[i], 1);
		ft_putstr_fd("   ", 1);
		print_right(i);
		ft_putstr_fd("\n", 1);
		i++;
	}
	ft_putstr_fd("\033[0m", 1);
}*/

// int main(void)
/*
int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;

	// Check for correct number of arguments
	if (argc != 1 || argv[1])
	{
		ft_putstr_fd("Usage: ./minishell\n", STDERR_FILENO);
		return (EXIT_FAILURE);
	}

	// Initialize the minishell structure
	if (!start_shell(&shell, envp))
	{
		ft_putstr_fd("Failed to start minishell\n", STDERR_FILENO);
		return (EXIT_FAILURE);
	}

	return (EXIT_SUCCESS);
}*/
/* ============ MAIN ============ */
int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;

	if (argc != 1 || argv[1])
	{
		ft_putstr_fd("Usage: ./minishell\n", STDERR_FILENO);
		return (EXIT_FAILURE);
	}

	if (start_shell(&shell, envp) != 0)
	{
		ft_putstr_fd("Failed to start minishell\n", STDERR_FILENO);
		return (EXIT_FAILURE);
	}

	//printf("ft_echo=%p ft_cd=%p ft_pwd=%p ft_export=%p ft_unset=%p ft_env=%p ft_exit=%p\n",
   // ft_echo, ft_cd, ft_pwd, ft_export, ft_unset, ft_env, ft_exit);

	looping(&shell);         // Boucle principale (readline, parsing, exec)
	free_minishell(&shell);  // Libère proprement toute la mémoire
	return (shell.exit_status);
}