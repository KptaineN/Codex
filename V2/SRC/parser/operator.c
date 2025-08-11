/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operator.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiefer <nkiefer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 09:40:01 by eganassi          #+#    #+#             */
/*   Updated: 2025/08/07 15:46:05 by nkiefer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int handle_heredoc(t_shell *shell, char **args)
{
  
    // Close previous fd_in to avoid leaks
	int i = ft_atoi(args[0]);
    if (shell->fd_in != -1 && shell->fd_in != STDIN_FILENO)
        close(shell->fd_in);
      int hd_pipe[2];
    if (pipe(hd_pipe) < 0)
	{
        perror("pipe");
        return -1;
    }

    // Check if delimiter is quoted (use your subtoken logic)
    // TRAVAIL: IL FAUT EXPAND !
    char *delimiter =shell->parsed_args->arr[i+1];

    // Read input until delimiter
    char *line;
    while ((line = readline("> "))) { // Requires readline.h
        if (strcmp(line, delimiter) == 0) {
            free(line);
            break;
        }
        // If not quoted, expand $variables (implement later with your subtoken logic)

        // Write line + newline to pipe
        write(hd_pipe[1], line, strlen(line));
        write(hd_pipe[1], "\n", 1);
        free(line);
    }

    close(hd_pipe[1]); // Close write end
    shell->fd_in = hd_pipe[0]; // Set read end as input
	return 0; // Success
}

// "<<",">>","&&","||","|","<",">"
//   0    1   2     3  	4   5   6
void file_access_redirection(t_shell *shell, int t_arr_index, int i)
{
    void **arr = shell->parsed_args->arr;
	if (i+1 >= shell->parsed_args->len)
		perror("Argument manquant pour l'opérateur"); // ERROR
	if (t_arr_index == 5)
	{
		if (shell->fd_in != -1) //<5 
		{
			shell->fd_in = open(arr[i+1], O_RDONLY);
			if (!shell->fd_in)
			 	perror("Erreur lors de l'ouverture en lecture"); // ERROR NOT OPENING;
		}
		else
		{
			if (access(arr[i+1], O_RDONLY) < 0)
				perror("ERROR ACCESS"); // ERROR NOT OPENING;
		}
		return;
	}
	if (t_arr_index == 0 && shell->fd_out != -1) //<< //HEREDOC
	{
		handle_heredoc(shell, *arr);
        return;
	}

	if (shell->fd_out != -1) // 1>> 6>  
	{
		if (t_arr_index == 1) 
		{
			shell->fd_out = open(arr[i+1] , O_CREAT | O_RDWR | O_TRUNC | O_APPEND, 0644);
			if (!shell->fd_out)
				perror("Erreur lors de l'ouverture en écriture (troncated)"); // ERROR SPACE
		}
		else if (t_arr_index == 6)
		{
			shell->fd_out = open(arr[i+1] , O_CREAT | O_RDWR | O_TRUNC , 0644);
			if (!shell->fd_out)
				perror("Erreur lors de l'ouverture en écriture (troncated)"); // ERROR SPACE
		}
		return;
	}
	if (t_arr_index == 6)
	{
		if (access(arr[i+1] , O_CREAT | O_RDWR | O_TRUNC) < 0)
			perror("Erreur lors de l'ouverture en écriture (troncated)"); // ERROR SPACE
	}
}
