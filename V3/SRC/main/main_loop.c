/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiefer <nkiefer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 16:24:16 by eganassi          #+#    #+#             */
/*   Updated: 2025/08/07 14:57:32 by nkiefer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"


/*** 1) Lecture de l’input ***/
char *read_user_input(void)
{
    char    *input;
    bool    interactive;

    interactive = isatty(STDIN_FILENO);
    if (interactive)
        input = readline("ᕕ( ᐛ )ᕗ minishell$ ");
    else
        input = get_next_line(STDIN_FILENO);
    if (!input)
    {
        if (interactive)
            write(1, "exit\n", 5);
        return (NULL);
    }
    if (!interactive)
    {
        size_t len = ft_strlen(input);
        if (len > 0 && input[len - 1] == '\n')
            input[len - 1] = '\0';
    }
    return (input);
}

/*** 2) Injection de $? ***/
char *expand_status(char *input, t_shell *sh)
{
    char *res = replace_exit_code(input, sh->exit_status);
    return (res);  // à free par l’appelant
}

/*** 3) Expansion des autres variables ***/
/* Cette fonction est supposée exister : replace_variables(const char*, t_shell*) */



/*
int looping(t_shell *shell)
{
	char  *input;
	char  *step1;
	char  *step2;

	while (1)
	{
		// 1) lire l’input
		input = read_user_input();
		if (!input)
			break;
		if (*input == '\0')
		{
			free(input);
			continue;
		}
		add_history(input);
		if (ft_strcmp(input, "exit") == 0) {
            free(input);
            break;
        }
		// 2) expansion de $?
		step1 = expand_status(input, shell);
		if (!step1)
		{
			free(input);
			continue;
		}

		// 3) expansion des variables
		step2 = replace_variables(step1, shell);
		free(step1);
		if (!step2)
		{
			free(input);
			continue;
		}

		// 4) Parsing avec le vrai parser (custom_split + attribute_token_type)
		shell->input = step2;
		shell->parsed_args = custom_split(step2, shell);
		if (!shell->parsed_args)
		{
			free(step2);
			free(input);
			continue;
		}

        // ——— RÉINITIALISATION DU PARSER ——— 
      
 
        // Attribution des types de tokens /
		attribute_token_type(shell);
		//4) Tokenisation + attribution du type 
        //attribute_token_type(shell);
 
        //Fallback : s'il y a des tokens mais pas de commande détectée,
         // on force n_cmd = 1 et on crée un cmd_head minimal.
		shell->n_cmd = 0;
        shell->cmd_head = NULL;
        shell->cmd_tail = NULL;
        if (shell->n_cmd == 0 && shell->n_tokens > 0)
        {
            shell->n_cmd = 1;
            //On pointe vers le 1er token comme commande unique 
            t_list *fallback = ft_lstnew(&shell->tokens[0]);
            if (!fallback) { perror("ft_lstnew fallback"); exit(1); }
            shell->cmd_head = fallback;
            shell->cmd_tail = fallback;
        }
		// print_commands(shell->parser.cmd_head);
		if (shell->n_cmd == 1) 
		{
            t_token *cmd = (t_token *)shell->cmd_head->content;
            if (cmd && cmd->value && ft_strcmp(cmd->value, "exit") == 0) 
			{
                free(step2);
                // free parser/env ici !
                break;
            }
        }
		shell->pids = malloc(sizeof(pid_t) * shell->n_cmd);
		if (!shell->pids)
			perror("MALLOC pids");
		// 5) Exécution
		launch_process(shell);
		// 6) Cleanup (ajuster selon ce qui est alloué)
		free_tab((char **)shell->parsed_args->arr);
		free(shell->parsed_args);
		free_tokens(shell);
        free_cmd_list(shell);
		shell->parsed_args = NULL;

		free_tokens(shell);

		t_list *it = shell->cmd_head;
  		while (it)
  		{
  		    t_list *next = it->next;
  		    free(it);
  		    it = next;
  		}
  		shell->cmd_head = NULL;
  		shell->cmd_tail = NULL;

		free(step2);
		free(input);
	}
	return (0);
}*/
int looping(t_shell *shell)
{
    char  *input;
    char  *step1;
    char  *step2;

    while (1)
    {
        // … lecture + expansions identiques …

		// 1) lire l’input
		input = read_user_input();
		if (!input)
			break;
		if (*input == '\0')
		{
			free(input);
			continue;
		}
		add_history(input);
		if (ft_strcmp(input, "exit") == 0) {
            free(input);
            break;
        }
		// 2) expansion de $?
		step1 = expand_status(input, shell);
		if (!step1)
		{
			free(input);
			continue;
		}

		// 3) expansion des variables
		step2 = replace_variables(step1, shell);
		free(step1);
		if (!step2)
		{
			free(input);
			continue;
		}

        /* 4) Parsing */
        shell->input = step2;
        shell->parsed_args = custom_split(step2, shell);
        if (!shell->parsed_args) { free(step2); free(input); continue; }

        /* Attribution des types */
        attribute_token_type(shell);

        /* Allocation & exécution */
        shell->pids = malloc(sizeof(pid_t) * shell->n_cmd);
        if (!shell->pids)
			{
				perror("MALLOC pids");
				free(step2);
				free(input);
				continue;
			}
        launch_process(shell);

        /* ========== CLEANUP ========== */
        /* 1) Les chaînes de parsed_args */
        free_str_array((char **)shell->parsed_args->arr);
        free(shell->parsed_args);
        shell->parsed_args = NULL;

        /* 2) Les tokens (tableau) */
		free_cmd_list(shell);
 		free_tokens(shell);

        /* 3) La liste des commandes (noeuds t_list) */
        
        /* 4) Le tableau des pids */
        free(shell->pids);
        shell->pids = NULL;

        /* 5) Les buffers */
        free(step2);
        free(input);
    }
    return 0;
}
