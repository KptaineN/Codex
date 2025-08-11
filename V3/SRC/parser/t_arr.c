/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_arr.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiefer <nkiefer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 22:08:28 by eganassi          #+#    #+#             */
/*   Updated: 2025/08/07 14:27:48 by nkiefer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// Add declarations for operator handler functions



/*array of string
size_t t_arrlen(void **arr)
{
    size_t len;

    if (!arr)
        return (0);
    
    len = 0;
    while (arr[len])
        len++;
    
    return (len);
}

/
	return (-1) not found
	return (%d != -1) idx of the one found in the array bcmd->arr
  
int is_in_t_arr_str(t_arr *arr, const char *arg)
{
    int i = 0;
    t_dic *dic;

    if (!arr || !arr->arr || !arg)
        return (-1);

    while (i < arr->len)
    {
        dic = (t_dic *)arr->arr[i];
        if (dic && dic->key && ft_strcmp(dic->key, arg) == 0)
            return (i);
        i++;
    }
    return (-1);
}


	For t_arr containing t_dic entries - searches by key
	return (-1) not found
	return (%d != -1) idx of the one found in the array
*int is_in_t_arr_dic_str(t_arr *arr, const char *arg)
{
    int i = 0;
    t_dic *dic;
    int len_key;
    int len_arg;
    
    if (!arr || !arg)
        return (-1);
    
    len_arg = 1 + (arg[1]!= 0);
    while (i < arr->len)
    {
        dic = (t_dic *)arr->arr[i];
        char *str = dic->key;
        (void)str;
        len_key = ft_trlen(dic->key);
        if (len_key<=len_arg)
        {
            if (dic && dic->key && ft_strncmp((char *)dic->key, arg, len_key) == 0)
                return (i);
        }
        i++;
    }
    return (-1);
}
int is_in_t_arr_dic_str(t_arr *arr, const char *arg)
{ 
    if (!arr || !arr->arr || !arg)
        return (-1);

    int i = 0;
    t_dic *dic;
    int len_key;
    int len_arg;
   
    
    len_arg = 1 + (arg[1]!= 0);
    while (i < arr->len)
    {
        if (!arr->arr[i]) 
        {
             printf("ERREUR: arr->arr[%d] == NULL\n", i);
            continue; // ou break;
        }
        dic = (t_dic *)arr->arr[i];
        if (!dic || !dic->key)
        {
            i++;
            continue;
        }
        //char *str = dic->key;
        len_key = ft_strlen(dic->key);
        if (len_key<=len_arg)
        {
            if (ft_strncmp(dic->key, arg, len_key) == 0)
                return (i);
        }
        i++;
    }
    return (-1);
}


// build the dynamic array of the builtins cmd
void build_t_arr_str(t_arr **dst, char **arr_str, int len)
{
    *dst = malloc(sizeof(t_arr));
    if (!*dst)
        return;
    
    (*dst)->len = len;
    (*dst)->arr = malloc(sizeof(char *) * len);
    if (!(*dst)->arr)
    {
        *dst = NULL;
        return;
    }
    
    int i = 0;
    while (i < len)
    {
        (*dst)->arr[i] = ft_strdup(arr_str[i]);
        if (!(*dst)->arr[i])
        {
            *dst = NULL;
            return;
        }
        i++;
    }
}

// build the dynamic array of t_dic entries
void build_t_arr_dic_str(t_arr **dst, char **keys, void **values, int len)
{
    *dst = malloc(sizeof(t_arr));
    t_dic *temp;
    if (!*dst)
        return;
    
    (*dst)->len = len;
    (*dst)->arr = malloc(sizeof(t_dic *) * len);   // OK: array of pointers
    if (!(*dst)->arr)
        return;

    temp = malloc(sizeof(t_dic) * len);            // FIXED: struct-sized blocks
    if (!temp)
        return;
    
    int i = 0;
    while (i < len)
    {
        temp[i].key   = ft_strdup(keys[i]);         // duplicate key
        temp[i].value = values[i];                  // store handler ptr
        (*dst)->arr[i] = &temp[i];                  // point into temp[]
        if (!temp[i].key)
            return;
        printf("%s\t%p\n", (char *)temp[i].key, (int*)temp[i].value);
        i++;
    }
}

// initialise the builtins and operators
void init_all_t_arr(t_shell *shell)
{
    char *all_operators[] = {"<<",">>","&&","||","|","<",">"};
    char *all_builtins[] = {"echo", "cd", "pwd", "export", "unset", "env", "exit"};
    void (*operator_handlers[])(t_shell *, int) = {
        handle_heredoc,     // "<<"
        handle_append,      // ">>"
        handle_and,         // "&&"
        handle_or,          // "||"
        handle_pipe,        // "|"
        handle_redirect_in, // "<"
        handle_redirect_out // ">"
    };
    int (*builtin_handlers[])(void *, int) = {
        ft_echo,
        ft_cd,
        ft_pwd,
        ft_export,
        ft_unset,
        ft_env,
        ft_exit,
    };
    int n_operateurs = sizeof(all_operators) / sizeof(char *);
    int n_builtins = sizeof(all_builtins) / sizeof(char *);

    build_t_arr_dic_str(&shell->parser.oper, all_operators, (void **)operator_handlers, n_operateurs);
    build_t_arr_dic_str(&shell->parser.bcmd, all_builtins, (void **)builtin_handlers, n_builtins);
}*/
  
size_t t_arrlen(void **arr)
{
    size_t len;
    
    if (!arr)
        return 0;
    len = 0;
    while (arr[len])
        len++;
    return len;
}

/*
    Retourne l'indice de la clé trouvée dans un t_arr de t_dic* (par clé exacte).
    -1 si non trouvé
*/
int is_in_t_arr_str(t_arr *arr, const char *arg)
{
    if (!arr || !arr->arr || !arg)
        return -1;
    int i = 0;
    while (i < arr->len)
    {
        t_dic *dic = (t_dic *)arr->arr[i];
        if (!dic || !dic->key)
        {
            i++;
            continue;
        }
        if (ft_strcmp(dic->key, arg) == 0)
            return (i);
        i++;
    }
    return (-1);
}

/*
    Pareil mais avec tolérance de longueur clé/arg (useless pour des builtins stricts, mais gardé si besoin)
*/
int is_in_t_arr_dic_str(t_arr *arr, const char *arg)
{
    if (!arr || !arr->arr || !arg)
        return -1;

    int i = 0;
    int len_arg = ft_strlen(arg);
    while (i < arr->len)
    {
        if (!arr->arr[i])
        {
            i++;
            continue;
        }

        t_dic *dic = (t_dic *)arr->arr[i];
        if (!dic || !dic->key)
        {
            i++;
            continue;
        }

        int len_key = ft_strlen(dic->key);
        if (len_arg >= len_key && ft_strncmp(arg, dic->key, len_key) == 0)
            return i;
        i++;
    }
    return -1;
}


/*
    Alloue un t_arr de strdup de string (pas utile pour tes builtins, tu utilises build_t_arr_dic_str normalement)
*/
void build_t_arr_str(t_arr **dst, char **arr_str, int len)
{
    *dst = malloc(sizeof(t_arr));
    if (!*dst)
        return;
    (*dst)->len = len;
    (*dst)->arr = malloc(sizeof(char *) * len);
    if (!(*dst)->arr)
    {
        free(*dst);
        *dst = NULL;
        return;
    }
    int i = 0;
    while ( i < len)
    {
        (*dst)->arr[i] = ft_strdup(arr_str[i]);
        if (!(*dst)->arr[i])
        {
            // clean (pas optimisé, à compléter si besoin)
            free(*dst);
            *dst = NULL;
            return;
        }
        i++;
    }
}
//fonction pour construire un t_arr de t_dic* (clé strdup + value copié direct, ex: ptr de handler)
//elle est differnete du parsing enrico peu etre responsable de la kaka
void build_t_arr_dic_str(t_arr **dst, char **keys,  int (**values)(t_shell *, char **), int len)
{
    *dst = malloc(sizeof(t_arr));
    if (!*dst)
        return;
    (*dst)->len = len;
    (*dst)->arr = malloc(sizeof(t_dic *) * len);
    if (!(*dst)->arr) {
        free(*dst);
        *dst = NULL;
        return;
    }
    int i = 0;
    while (i < len)
    {
        if (!keys[i] || !values[i])
        {
            // Si une clé ou un handler est NULL, on ne peut pas continuer
            // On pourrait gérer ça différemment si besoin, mais pour l'instant on arrête ici
            free(*dst);
            *dst = NULL;
            return;
        }
        t_dic *dic = malloc(sizeof(t_dic));
        if (!dic)
        {
            // Free tout ce qui a été déjà alloué
            int j = 0;
            while (j < i)
            {
                t_dic *prev = (t_dic *)(*dst)->arr[j];
                free(prev->key);
                free(prev);
                j++;
            }
            free((*dst)->arr);
            free(*dst);
            *dst = NULL;
            return;
        }
        dic->key = ft_strdup(keys[i]);
        dic->value = values[i];
        //printf("[BUILD] key=%s, handler=%p\n",  (char *)dic->key, (void *)dic->value); // wildjump
        if (!dic->key)
        {
            free(dic);
            for (int j = 0; j < i; j++) {
                t_dic *prev = (t_dic *)(*dst)->arr[j];
                free(prev->key);
                free(prev);
            }
            free((*dst)->arr);
            free(*dst);
            *dst = NULL;
            return;
        }
        (*dst)->arr[i] = dic;
        // Debug print:
        // printf("build_t_arr_dic_str: [%d] key='%s', value=%p\n", i, (char *)dic->key, (void *)dic->value);
        i++;
    }
}

/*
    Alloue un t_arr de t_dic* (clé strdup + value copié direct, ex: ptr de handler)
    Sécurise tous les mallocs et print debug.

void build_t_arr_dic_str(t_arr **dst, char **keys, void **values, int len)
{
    *dst = malloc(sizeof(t_arr));
    if (!*dst)
        return;
    (*dst)->len = len;
    (*dst)->arr = malloc(sizeof(t_dic *) * len);
    if (!(*dst)->arr) {
        free(*dst);
        *dst = NULL;
        return;
    }
    // On utilise un tableau temporaire pour éviter des free sauvages
    t_dic *temp = malloc(sizeof(t_dic) * len);
    if (!temp) {
        free((*dst)->arr);
        free(*dst);
        *dst = NULL;
        return;
    }
    for (int i = 0; i < len; i++)
    {
        temp[i].key   = ft_strdup(keys[i]);
        temp[i].value = values[i];
        (*dst)->arr[i] = &temp[i];
        if (!temp[i].key) {
            // Free all before i
            for (int j = 0; j < i; j++) free(temp[j].key);
            free(temp);
            free((*dst)->arr);
            free(*dst);
            *dst = NULL;
            return;
        }
        // Debug print:
        // printf("build_t_arr_dic_str: [%d] key='%s', value=%p\n", i, temp[i].key, temp[i].value);
    }
}*/

/*
    Initialise tous les builtins et opérateurs dans la shell (via bcmd et oper)
*/
void init_all_t_arr(t_shell *shell)
{
    char *all_operators[] = {"<<", ">>", "&&", "||", "|", "<", ">"};
    char *all_builtins[] = {"echo", "cd", "pwd", "export", "unset", "env", "exit"};
    int (*operator_handlers[])(t_shell *, char **) = {
        handle_heredoc,     // "<<"
        handle_append,      // ">>"
        handle_and,         // "&&"
        handle_or,          // "||"
        handle_pipe,        // "|"
        handle_redirect_in, // "<"
        handle_redirect_out // ">"
    };
    int (*builtin_handlers[])(t_shell *, char **) = {
        ft_echo,
        ft_cd,
        ft_pwd,
        ft_export,
        ft_unset,
        ft_env,
        ft_exit,
    };
    int n_operateurs = sizeof(all_operators) / sizeof(char *);
    int n_builtins = sizeof(all_builtins) / sizeof(char *);

    build_t_arr_dic_str(&shell->oper, all_operators, operator_handlers, n_operateurs);
    build_t_arr_dic_str(&shell->bcmd, all_builtins, builtin_handlers, n_builtins);
}
