/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util-0.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiefer <nkiefer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 16:30:56 by eganassi          #+#    #+#             */
/*   Updated: 2025/06/26 08:23:23 by nkiefer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
// Assemble trois chaînes (ex: "bin", "/", "ls" -> "bin/ls")
char	*ft_strjoin_3(const char *a, const char *b, const char *c)
{
	char	*tmp;
	char	*res;

	tmp = ft_strjoin(a, b);
	if (!tmp)
		return (NULL);
	res = ft_strjoin(tmp, c);
	free(tmp);
	return (res);
}

char	*ft_tripljoinstring(char *s1, char *s2, char *s3)
{
	char	*tmp = ft_strjoin(s1, s2);
	char	*res = ft_strjoin(tmp, s3);
	free(s1);
	free(tmp);
	return (res);
}*/
// Concatène a + b + c. Si free_a est 1, libère 'a' après usage.
// Utile pour accumuler dynamiquement (ex: res = join3_and_free(res, x, y, 1))
char	*ft_strjoin3(char *a, const char *b, const char *c, int free_a)
{
	char	*tmp;
	char	*res;

	if (!a || !b || !c)
		return (NULL);
	tmp = ft_strjoin(a, b);
	if (!tmp)
		return (NULL);
	res = ft_strjoin(tmp, c);
	free(tmp);
	if (free_a)
		free(a);
	return (res);
}


void	handle_error(const char *message)
{
	perror(message);
	exit(EXIT_FAILURE);
}

/*void handle_signal(int signal)
{
	if (signal == SIGINT)
	{
		// Handle Ctrl+C
		write(STDOUT_FILENO, "\n", 1); // Print a newline
		rl_replace_line("", 0); // Clear the current line in readline
		rl_on_new_line(); // Move to a new line
		rl_redisplay(); // Redisplay the prompt
	}
	else if (signal == SIGQUIT)
	{
		// Handle Ctrl+\ (SIGQUIT)
		write(STDOUT_FILENO, "Quit (core dumped)\n", 19);
	}
}*/
/*void	print_prompt(t_shell *shell)
{
	// You can customize the prompt here, e.g.,
	//	add colors or display the current directory
	char *cwd = getcwd(NULL, 0); // Get current working directory
	if (cwd)
	{
		printf("\033[1;32m%s\033[0m$ ", cwd); // Print in green color
		free(cwd);
	}
	else
	{
		printf("minishell$ ");
	}
}*/
