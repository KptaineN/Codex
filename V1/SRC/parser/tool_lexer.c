/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tool_lexer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiefer <nkiefer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 22:24:17 by eganassi          #+#    #+#             */
/*   Updated: 2025/08/11 13:54:30 by nkiefer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "../../include/parsking.h"
#include "../../include/minishell.h"



/*
 * Vérifie si le caractère à l’indice idx n’est pas échappé
 * par un nombre impair de backslashes précédents.
 */
bool escape_check(const char *str, int idx)
{
    bool toggle = true;
    while (idx > 0 && str[--idx] == '\\')
        toggle = !toggle;
    return toggle;
}


/*
	trouve la premiere occurence de charactere
	str = Enrico et Noe sont beau
	needle = "o" (size 1)				return: "o et Noe sont beau"
	needle = "Nc" (size 2)				return: "co et Noe sont Beau"
	du coup c'est un strchr mais que si tu voulais chercher "N" et "c" 
	et voulais prendre le premier d'entre eux, ici elle te retourne naturellement le premier
	
	UTILISÉ dans 'token_attribute_parts_type' pour quand de UNQUOTED on passe a SINGLE/DOUBLE QUOTED mais on sais pas le quel
*/
int find_c_nonescaped(const char *str, char *needle, int size_needle)
{
	int c;
	int idx = 0;

	while (str[idx])
	{
		c = 0;
		while(c<size_needle && str[idx])
		{
			if (str[idx] == needle[c] && escape_check(str,idx))
				return idx;
			c++;
		}
		idx++;
	}
	return idx;
}

/*
	Ici on token les subtokens
*/
int count_subtokens(const char *str)
{
	bool in_single_quote;
	bool in_double_quote;
	bool in_no_quote;
	int i = 0;
	int count = 0;

	in_single_quote = 0;
	in_double_quote = 0;
	in_no_quote = 0;
	while(str[i])
	{
		if (str[i] == '\"' && !in_single_quote && escape_check(str,i))
		{
			in_no_quote = false;
			in_double_quote =!in_double_quote;
			if (in_double_quote)
				count++;
		}
		else if (str[i] == '\'' && !in_double_quote && escape_check(str,i))
		{
			in_no_quote = false;
			in_single_quote =!in_single_quote;
			if (in_single_quote)
				count++;
		}
		else if (!in_single_quote && !in_double_quote && !in_no_quote)
		{	
			count++;
			in_no_quote = true;
		}
		i++;
	}
	return count;
}

/* =============================
 * Compte le nombre de commandes
 * ============================= */
int count_tokens(t_shell *shell, t_arr *parsed_args, t_arr *oper)
{
    int count = 1;
    int i = 0;
    int len;
    int idx_oper;

    if (!parsed_args || !parsed_args->arr)
        return 0;

    len = parsed_args->len;
    if (len == 0)
        return 0;

    while (i < len)
    {
        idx_oper = is_in_t_arr_dic_str(oper, parsed_args->arr[i]);
        if (idx_oper != -1)
        {
            if (idx_oper < 2 || idx_oper > 4)
            {
                file_access_redirection(shell, parsed_args->arr, idx_oper, i);
                i += 2;
                continue;
            }
            else
            {
                count++;
            }
        }
        i++;
    }
    return count;
}

/* =============================
 * Gestion des sous-tokens
 * ============================= */
int attribute_cmd_subtokens(t_shell *shell, t_token *cmd_token, int idx, int len)
{
    if (!shell || !cmd_token || !shell->parsed_args || !shell->parsed_args->arr)
        return idx + 1;

    if (len <= 0)
        return idx + 1;

    t_arr *arr_arg = shell->parsed_args;
    char **args = (char **)arr_arg->arr;
    t_subtoken_container *containers = calloc(len + 1, sizeof(t_subtoken_container));
    if (!containers)
        return idx + len;

    cmd_token->cmd_args_parts = containers;
    cmd_token->n_args = len;

    //printf("[DEBUG] attribute_cmd_subtokens: len = %d, idx = %d\n", len, idx);
    for (int k = 0; k < len && idx < arr_arg->len; k++, idx++)
    {
        containers[k].n_parts = count_subtokens(args[idx]);
        if (containers[k].n_parts > 0)
        {
            containers[k].parts = malloc(sizeof(t_subtoken) * containers[k].n_parts);
            subtoken_of_cmd(&containers[k], args[idx]);
        }
    }

    containers[len].n_parts = 0;
    containers[len].parts = NULL;

    return idx;
}

/* =============================
 * Découpage d'un argument
 * ============================= */
void subtoken_of_cmd(t_subtoken_container *container, char *arg)
{
    if (!container || !arg || container->n_parts <= 0)
        return;

    int i = 0, idx = 0, idx_tail = 0, arg_len = ft_strlen(arg);
    t_subtoken *parts = container->parts;

    while (idx < arg_len && i < container->n_parts)
    {
        if (arg[idx] == '\'' && escape_check(arg, idx))
        {
            int start = idx + 1;
            idx_tail = find_c_nonescaped(&arg[start], "\'", 1);
            if (idx_tail < 0) idx_tail = arg_len - start;
            parts[i].type = QUOTE_SINGLE;
            parts[i].p = ft_substr(arg, start, idx_tail);
            parts[i].len = idx_tail;
            idx = start + idx_tail + 1;
        }
        else if (arg[idx] == '"' && escape_check(arg, idx))
        {
            int start = idx + 1;
            idx_tail = find_c_nonescaped(&arg[start], "\"", 1);
            if (idx_tail < 0) idx_tail = arg_len - start;
            parts[i].type = QUOTE_DOUBLE;
            parts[i].p = ft_substr(arg, start, idx_tail);
            parts[i].len = idx_tail;
            idx = start + idx_tail + 1;
        }
        else
        {
            int start = idx;
            idx_tail = find_c_nonescaped(&arg[start], "\"\'", 2);
            if (idx_tail < 0) idx_tail = arg_len - start;
            parts[i].type = QUOTE_NONE;
            parts[i].p = ft_substr(arg, start, idx_tail);
            parts[i].len = idx_tail;
            idx = start + idx_tail;
        }
        i++;
    }
}

/* =============================
 * Attribution du type de token
 * ============================= */
void attribute_token_type(t_shell *shell)
{
    int i = 0, idx_token = 0;
    void **arr = shell->parsed_args->arr;

    if (!arr || shell->parsed_args->len <= 0)
    {
        shell->n_tokens = 0;
        return;
    }

    shell->n_tokens = count_tokens(shell, shell->parsed_args, shell->oper);
    shell->tokens = (t_token *)calloc(shell->n_tokens, sizeof(t_token));
    if (!shell->tokens)
    {
        perror("Erreur allocation tokens");
        exit(EXIT_FAILURE);
    }

    while (i < shell->parsed_args->len && idx_token < shell->n_tokens)
    {
        t_token *token = &shell->tokens[idx_token];
        //token->value = arr[i]; // If arr[i] is reused elsewhere, consider duplicating with strdup(arr[i])
        token->value = ft_strdup(arr[i]);
        if (!token->value)
        {
            perror("Erreur allocation token value");
            exit(EXIT_FAILURE);
        }
        if (is_in_t_arr_dic_str(shell->oper, arr[i]) != -1)
        {
            token->type = TOKEN_OPER;
            i++;
        }
        else
        {
            token->type = (is_in_t_arr_str(shell->bcmd, arr[i]) != -1) ? TOKEN_BCMD : TOKEN_CMD;

            int nb_args = count_args_cmd(shell, i);
            //printf("[DEBUG] attribute_token_type: token '%s' has %d args\n", token->value, nb_args);
            if (nb_args <= 0) nb_args = 1;

            int new_i = attribute_cmd_subtokens(shell, token, i, nb_args);
            //printf("[DEBUG] attribute_token_type: new_i = %d, i = %d\n", new_i, i);
            i = (new_i > i) ? new_i : i + 1;
        }
        idx_token++;
    }
}


