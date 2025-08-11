/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiefer <nkiefer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 16:35:53 by eganassi          #+#    #+#             */
/*   Updated: 2025/07/28 12:37:04 by nkiefer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"



#include <sys/ioctl.h>
#include <unistd.h>
#include <stdio.h>
#include <time.h>

/* Fait défiler un 🦆 de la colonne la plus à droite jusqu'à la 0,
   puis efface la ligne pour retrouver l'invite proprement. */
static void single_quack(void)
{
	struct winsize ws;
    if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws) == -1)
        return;
    int cols = ws.ws_col;

    const char *frames[] = { "𓆝", "𓆟", "𓆞" };
    const int nframes = 3;
    struct timespec ts = { .tv_sec = 0, .tv_nsec = 30000000L };  /* 50 ms */

    /* Cache le curseur & sauve la position juste après le prompt */
    printf("\033[?25l\033[s");
    fflush(stdout);

    int prev_x = -1;
    for (int t = 0; ; ++t)
    {
        int x = cols - 1 - t;
        if (x < 0)
            break;
        int f = t % nframes;

        /* Efface l’ancienne position */
        if (prev_x >= 0) {
            printf("\033[u\033[%dC ", prev_x);
            fflush(stdout);
        }
        /* Affiche la nouvelle frame */
        printf("\033[u\033[%dC%s", x, frames[f]);
        fflush(stdout);

        nanosleep(&ts, NULL);
        prev_x = x;
    }

    /* Efface la dernière trace */
    if (prev_x >= 0) {
        printf("\033[u\033[%dC ", prev_x);
        fflush(stdout);
    }

    /* Restaure curseur et prompt */
    printf("\033[u\033[?25h");
    fflush(stdout);

    /* Clear entire screen and move cursor to top-left */
    printf("\033[2J\033[H");
    fflush(stdout);
}

int count_subtoken_args(t_subtoken_container *args)
{
	int count = 0;
	while (args[count].n_parts > 0)
		count++;
	return count;
}

/*char **reconstruct_args(t_subtoken_conainter *args)
{
	int count = count_subtoken_args(args); // tu peux créer ça si tu veux, ou faire simple
	char **res = malloc(sizeof(char *) * (count + 1));
	if (!res)
		return NULL;

	for (int i = 0; i < count; i++)
	{
		int total_len = 0;
		for (int j = 0; j < args[i].n_parts; j++)
			total_len += args[i].parts[j].len;

		res[i] = malloc(total_len + 1);
		if (!res[i])
			return NULL; // (libère avant dans un vrai code)
		int pos = 0;
		for (int j = 0; j < args[i].n_parts; j++)
		{
			ft_memcpy(res[i] + pos, args[i].parts[j].p, args[i].parts[j].len);
			pos += args[i].parts[j].len;
		}
		res[i][pos] = '\0';
	}
	res[count] = NULL;
	return res;
}*/

// Concatène tous les subtokens dans un seul string (sans quotes)
/*char *join_subtokens(t_subtoken_container container)
{
	if (container.count == 0)
		return (NULL);

	int total_len = 0;
	for (int i = 0; i < container.count; i++)
		total_len += container.parts[i].len;

	char *res = malloc(total_len + 1);
	if (!res)
		return (NULL);

	int offset = 0;
	for (int i = 0; i < container.count; i++)
	{
		ft_memcpy(res + offset, container.parts[i].p, container.parts[i].len);
		offset += container.parts[i].len;
	}
	res[offset] = '\0';

	return res;
}


char **reconstruct_args(t_subtoken_container *parts)
{
    int count = count_subtoken_args(parts);
    if (count == 0)
        return NULL;

    char **args = malloc(sizeof(char *) * (count + 1));
    if (!args)
        return NULL;

    for (int i = 0; i < count; i++)
    {
        args[i] = join_subtokens(parts[i]); // <- fonction à toi qui assemble chaque part
        if (!args[i])
        {
            free_tab(args);
            return NULL;
        }
    }
    args[count] = NULL;

    return args;
}*/



/* builtin_quack simplifié pour un seul passage */
int builtin_quack(char **args)
{
    (void)args;       /* on n'utilise pas args ici */
    single_quack();
    return 0;
}

int match_str(t_subtoken sub, const char *str)
{
    printf("[DEBUG] matching '%.*s' with '%s'\n", sub.len, sub.p, str);
	return (ft_strncmp(sub.p, str, sub.len) == 0 && str[sub.len] == '\0');
}
int is_builtin(const char *cmd)
{
    return (
        ft_strcmp(cmd, "cd") == 0 ||
        ft_strcmp(cmd, "echo") == 0 ||
        ft_strcmp(cmd, "pwd") == 0 ||
        ft_strcmp(cmd, "export") == 0 ||
        ft_strcmp(cmd, "unset") == 0 ||
        ft_strcmp(cmd, "env") == 0 ||
        ft_strcmp(cmd, "exit") == 0
    );
}





/*int execute_builtin(t_shell *shell, int token_idx)
{
    t_token *tok = &shell->parser.tokens[token_idx];
    t_subtoken first = tok->cmd_args_parts[0].parts[0];

    // Export prend directement le token
    if (match_str(first, "export"))
        return builtin_export(tok, shell);

   // char **args = reconstruct_args(tok->cmd_args_parts);

    if (match_str(first, "cd"))
        return builtin_cd(args, shell);
    if (match_str(first, "echo"))
        return builtin_echo(shell, tok);
    if (match_str(first, "pwd"))
        return builtin_pwd();
    if (match_str(first, "exit"))
        return builtin_exit(shell, tok);
    if (match_str(first, "unset"))
        return builtin_unset(args, shell);
    if (match_str(first, "env"))
        return builtin_env(args, shell);
    if (match_str(first, "duck"))
    {
        ft_putstr_fd("Quack! 🦆\n", STDOUT_FILENO);
        free_tab(args);
        return 0;
    }
    printf("[DEBUG] execute_builtin: got command = ");
    write(1, first.p, first.len);
    printf("\n");

    free_tab(args);
    return 1;
}*/


		//return (builtin_env(shell->args, shell));
	// Si on arrive ici, c'est que la commande n'est pas un builtin reconnu
	//ft_putstr_fd("minishell: ", STDERR_FILENO);
	//ft_putstr_fd(ast->args[0], STDERR_FILENO);
	//ft_putstr_fd(": command not found\n", STDERR_FILENO);


