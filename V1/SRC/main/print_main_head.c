/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_main_head.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiefer <nkiefer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 15:16:18 by nkiefer           #+#    #+#             */
/*   Updated: 2025/08/16 13:53:14 by nkiefer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static const char	**get_left_logo(void)
{
	static const char	*logo[] = {
		"                                                          ",
		"      ███▄ ▄███▓ ██▓ ███▄    █  ██▓  ██████  ██░ ██ ▓█████"
		"  ██▓     ██▓      ",
		"     ▓██▒▀█▀ ██▒▓██▒ ██ ▀█   █ ▓██▒▒██    ▒ ▓██░ ██▒▓█   ▀"
		" ▓██▒    ▓██▒      ",
		"     ▓██    ▓██░▒██▒▓██  ▀█ ██▒▒██▒░ ▓██▄   ▒██▀▀██░▒███"
		"   ▒██░    ▒██░      ",
		"     ▒██    ▒██ ░██░▓██▒  ▐▌██▒░██░  ▒   ██▒░▓█ ░██ ▒▓█  ▄"
		" ▒██░    ▒██░      ",
		"     ▒██▒   ░██▒░██░▒██░   ▓██░░██░▒██████▒▒░▓█▒░██▓░▒████▒"
		"░██████▒░██████▒  ",
		"     ░ ▒░   ░  ░░▓  ░ ▒░   ▒ ▒ ░▓  ▒ ▒▓▒ ▒ ░ ▒ ░░▒░▒░░ ▒░ ░"
		"░ ▒░▓  ░░ ▒░▓  ░  ",
		"      ░  ░      ░ ▒ ░░ ░░   ░ ▒░ ▒ ░░ ░▒  ░ ░ ▒ ░▒░ ░ ░ ░  ░"
		"░ ░ ▒  ░░ ░ ▒  ░ ",
		"      ░      ░    ▒ ░   ░   ░ ░  ▒ ░░  ░  ░   ░  ░░ ░   ░"
		"     ░ ░     ░ ░    ",
		"           ░    ░           ░  ░        ░   ░  ░  ░   ░  ░"
		"    ░  ░    ░  ░   ",
		"                                                          ",
		NULL
	};

	return (logo);
}

static const char	**get_left_credits(void)
{
	static const char	*credits[] = {
		"          )))         ╔╗╔┌─┐┌─┐   ┬   ╔═╗┌┐┌┬─┐┬┌─┐┌─┐"
		"          (((          ",
		"         (o o)        ║║║│ │├┤   ┌┼─  ║╣ │││├┬┘││  │ │"
		"         (o o)         ",
		"        --(_)--       ╝╚╝└─┘└─┘  └┘   ╚═╝┘└┘┴└─┴└─┘└─┘"
		"        --(_)--        ",
		NULL
	};

	return (credits);
}

static const char	**get_left(void)
{
	const char			**logo;
	const char			**credits;
	static const char	*combined[20];
	int					i;
	int					j;

	logo = get_left_logo();
	credits = get_left_credits();
	i = 0;
	j = 0;
	while (logo[i])
		combined[j++] = logo[i++];
	i = 0;
	while (credits[i])
		combined[j++] = credits[i++];
	combined[j] = NULL;
	return ((const char **)combined);
}

static void	print_right(int i)
{
	static const char	*right[] = {
		"",
		"⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⡠⠤⠖⢒⠂⢤⣀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀",
		"⢀⣟⣿⣦⠀⠀⠀⣰⡿⠿⠷⠶⣄⠀⠀⢠⠾⠟⠛⠛⢷⡀⠀⢀⡼⣿⣇⡇",
		"⠈⠛⠛⠿⢕⡂⢴⠁⠀⠀⠀⢀⠈⠆⠠⣮⣴⢤⡀⣀⣸⣗⣶⡧⠒⠉⠉⠁",
		"⠀⠀⠀⠀⠀⢹⠀⠀⠴⣺⣿⣿⠇⠀⠀⠛⡿⣽⣿⣽⠿⠛⢻⠀⠀⠀⠀⠀",
		"⠀⠀⠀⠀⠀⡌⠀⠀⠈⠉⢩⠀⠀⠀⠀⠀⣸⣒⣄⠀⠀⠀⠀⠇⠀⠀⠀⠀",
		"⠀⠀⠀⠀⠀⡇⠀⢀⡴⠖⠉⠛⠓⠲⠶⠾⠿⠿⠿⢏⡳⡀⠄⣾⠀⠀⠀⠀",
		"⠀⠀⠀⠀⠀⠃⠀⠞⠀⣀⣀⣀⣀⣀⣀⣀⣤⣤⣶⣿⣇⢧⠀⣿⠀⠀⠀⠀",
		"⠀⠀⠀⠀⠀⡄⠀⠀⠀⠈⠫⢽⣽⣉⣹⣁⣧⣿⠟⣱⣿⣾⢀⣿⠀⠀⠀⠀",
		"⠀⠀⠀⠀⠀⢃⠀⠀⠀⠀⠀⠀⠉⠙⠩⠤⠭⣶⣋⡟⢸⢁⣿⠏⠀⠀⠀⠀",
		"			      ⠱ ⡀⠀⠀⠀⠀⠀⠀⠀⠈⠛⠝⡇⣘⡾⠋⠀⠀⠀⠀⠀",
		"⠀⠀⠀⠀⠀⠀⠀⠈⠢⣀⠀⠀⠀⠀⠀⠀⠀⣠⣴⣷⠋⠀⠀⠀⠀⠀⠀⠀",
		"⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠑⠠⠤⠤⠤⠤⠾⠟⠋⠁⠀⠀⠀⠀⠀⠀⠀⠀",
		"",
		NULL
	};

	if (right[i])
		ft_putstr_fd((char *)right[i], 1);
}

void	print_header_emote(void)
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
}
