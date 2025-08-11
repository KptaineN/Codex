/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiefer <nkiefer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 16:24:19 by eganassi          #+#    #+#             */
/*   Updated: 2025/08/07 17:32:12 by nkiefer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"



/* Initialise les champs de base du shell */
void init_idx(t_shell *shell)
{

    /* Descripteurs par défaut */
    shell->fd_in = -1;
	shell->fd_out = -1;
    shell->fd_in  = STDIN_FILENO;
    shell->fd_out = STDOUT_FILENO;

    /* Pas de heredoc pour l'instant */
    shell->heredoc = NULL;

    /* Comptages et pointeurs initiaux */
    shell->n_tokens   = 0;
    shell->n_cmd      = 0;
    shell->tokens     = NULL;
    shell->cmd_head   = NULL;
    shell->cmd_tail   = NULL;
    shell->pids       = NULL;
    shell->fd_pid[0]  = -1;
    shell->fd_pid[1]  = -1;
    shell->parsed_args= NULL;
    shell->bcmd       = NULL;
    shell->oper       = NULL;
}

/* Initialise le shell avant la boucle */
void init_shell(t_shell *shell, char **envp)
{
    if (!shell || !envp)
        return;

    shell->args        = NULL;
    shell->exit_status = 0;
    shell->input       = NULL;

    /* On passe shell, pas &shell */
    init_idx(shell);
}

/* Démarrage du shell */
int start_shell(t_shell *shell, char **envp)
{
    if (!shell)
        return 1;

    ft_bzero(shell, sizeof(t_shell));
    init_signals();
     //shell->env = init_env(envp);
    shell->env = set_linked_path(envp); // Initialisation de l'environnement
    init_shell(shell, envp);
    if (!shell->env)
    {
        perror("Error initializing environment");
        return 1;
    }
    init_all_t_arr(shell);
    return 0;
}
