/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util-3-free.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiefer <nkiefer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 16:27:38 by eganassi          #+#    #+#             */
/*   Updated: 2025/08/07 17:21:53 by nkiefer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"


void free_t_arr_dic(t_arr *array)
{
    if (!array)
        return;
    if (array->arr)
    {
        for (int i = 0; i < array->len; i++) {
            t_dic *dic = (t_dic *)array->arr[i];
            if (dic) {
                if (dic->key)
                    free(dic->key);
                free(dic);
            }
        }
        free(array->arr);
    }
    free(array);
}


/* ========================================
 * Libère un tableau de chaînes de type char**
 * ======================================== */
void free_tab(char **tab)
{
    int i;

    if (!tab)
        return;
    for (i = 0; tab[i]; i++)
        free(tab[i]);
    free(tab);
}

/* ========================================
 * Libère un tableau dynamique t_arr
 * ======================================== */
void free_t_arr(t_arr *array)
{
    if (!array)
        return;
    if (array->arr)
    {
        for (int i = 0; i < array->len; i++)
            free(array->arr[i]);
        free(array->arr);
    }
    free(array);
}

/* ========================================
 * Libère la liste chaînée de l'environnement
 * Chaque content doit être (char *) ou une struct allouée.
 * ======================================== */
void free_list_str(t_list *lst)
{
    t_list *tmp;

    while (lst)
    {
        tmp = lst->next;
        if (lst->content)
            free(lst->content);
        free(lst);
        lst = tmp;
    }
}

void free_env(t_list *env)
{
    free_list_str(env);
}
void free_str_array(char **arr)
{
    if (!arr) {
        printf("[DEBUG] free_str_array: arr == NULL\n");
        return;
    }
    for (int i = 0; arr[i]; i++)
        free(arr[i]);
    free(arr);
}


void free_cmd_list(t_shell *shell)
{
    t_list *node = shell->cmd_head;
    while (node)
    {
        t_list *next = node->next;
        free(node);
        node = next;
    }
    shell->cmd_head = NULL;
    shell->cmd_tail = NULL;
    shell->n_cmd    = 0;
}

void ft_free(void **thing)
{
    if (!*thing)
        return;
    free(*thing);
    *thing = NULL;
}


/* ========================================
 * Libère les tokens (liste chaînée t_token)
 * ======================================== */
/* ========================================
 * Libère le tableau de tokens (tableau, pas liste)
 * ======================================== */

void free_tokens(t_shell *shell)
{
    if (!shell || !shell->tokens)
        return;

    for (int i = 0; i < shell->n_tokens; i++)
    {
        t_token *tok = &shell->tokens[i];
        // Libère tous les sous-tokens de chaque arg
        if (tok->cmd_args_parts)
        {
            for (int j = 0; j < tok->n_parts; j++)
            {
                t_subtoken_container *cont = &tok->cmd_args_parts[j];
                if (cont->parts)
                {
                    for (int k = 0; k < cont->n_parts; k++)
                    {
                        // Si tu as fait ft_substr ou ft_strdup sur parts[k].p, free-le
                        if (cont->parts[k].p)
                        {
                         //   printf("[DEBUG] free_tokens 138: freeing part %d of token '%s'\n", k, tok->value);
                         //   printf("[DEBUG] free_tokens: freeing part %d of token '%s' (p: %p, val: %.10s)\n", 
                         //       k, tok->value ? tok->value : "(null)", cont->parts[k].p, cont->parts[k].p);
                         //   free(cont->parts[k].p);
                        //    printf("[DEBUG] free_tokens 140: freed part %d of token '%s'\n", k, tok->value);
                        }
                    }
                    free(cont->parts);
             //       printf("[DEBUG] free_tokens 144: freed parts of token '%s'\n", tok->value);
                }
            }
            free(tok->cmd_args_parts);
            tok->value = NULL;
        }
        // Si value = strdup/ft_substr => free, sinon ne pas toucher
        // (mais dans ton parsing c’est souvent juste un pointeur du split, donc ne rien faire)
    }

    free(shell->tokens);
  //  printf("[DEBUG] free_tokens 163: freed all tokens\n");
    shell->tokens   = NULL;
    shell->n_tokens = 0;
    
}



void free_subtoken_container(t_subtoken_container *container)
{
    if (!container)
        return;
    if (container->parts)
    {
        for (int i = 0; i < container->n_parts; i++)
        {
            t_subtoken *sub = &container->parts[i];
            if (sub->p)
                free(sub->p); // Libère le pointeur de chaque sous-token
        }
        free(container->parts);
    }
    free(container);
}
/* ========================================
 * Libère tout le parser
 * ======================================== */
void free_parser(t_shell *parser)
{
    if (!parser)
        return;

    //free_tokens(parser);
    if (parser->parsed_args)
        free_t_arr(parser->parsed_args);
    parser->parsed_args = NULL;

    if (parser->bcmd)
        free_t_arr_dic(parser->bcmd);
    parser->bcmd = NULL;

    if (parser->oper)
        free_t_arr_dic(parser->oper);
    parser->oper = NULL;

    if (parser->env)
        free_list_str(parser->env);
    parser->env = NULL;
}

/* ========================================
 * Libère toute la structure minishell
 * ======================================== */
void free_minishell(t_shell *shell)
{
    if (!shell)
        return;

    free_parser(shell);
    if (shell->args)
        free_str_array(shell->args);
    shell->args = NULL;
}

#include <unistd.h>  // pour _exit

void child_exit(char **args,
                char *cmd_path,
                char **envp,
                t_list *candidates,
                int code)
{
    if (envp)     free_str_array(envp);
    if (args)     free_str_array(args);
    if (cmd_path) free(cmd_path);
    if (candidates) free_list_str(candidates);
    _exit(code);
}




// Fichier : exit_utils.c par exemple
void	exit_shell(t_shell *shell, int exit_code)
{
	free_minishell(shell);
	rl_clear_history(); // nettoie readline
	exit(exit_code);
}

