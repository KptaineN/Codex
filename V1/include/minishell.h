/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiefer <nkiefer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 16:45:17 by nkiefer           #+#    #+#             */
/*   Updated: 2025/07/28 14:26:58 by nkiefer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define _POSIX_C_SOURCE 200809L

# include "LIBFT/libft.h"


# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>



/* =============================
 * STRUCTURES GENERALES
 * ============================= */
typedef struct s_list
{
    void            *content;
    struct s_list   *next;
}   t_list;

typedef struct s_env
{
    char    *key;
    char    *value;
}   t_env;

typedef struct s_arr
{
    void            **arr;
    int             len;
}   t_arr;

struct s_shell; // AVANT la déclaration de t_dic !
typedef struct s_shell t_shell;
typedef struct s_dic
{
    void *key;
    int (*value)(t_shell *, char **); // plus besoin de cast !
    //void *value;
}   t_dic;

typedef enum e_toktype
{
    TOKEN_WORD,
    TOKEN_BCMD,
    TOKEN_CMD,
    TOKEN_OPER
}   t_toktype;

typedef enum e_quote_type
{
    QUOTE_NONE,
    QUOTE_SINGLE,
    QUOTE_DOUBLE
}   t_quote_type;

typedef struct s_subtoken
{
    t_quote_type    type;
    char            *p;
    int             len;
}   t_subtoken;

typedef struct s_subtoken_container
{
    t_subtoken      *parts;
    int             n_parts;
}   t_subtoken_container;

/* Forward declaration to allow pointers before full definition */
typedef struct s_redir t_redir;

typedef struct s_token
{
    char                    type;
    char                    *value;
    t_subtoken_container    *cmd_args_parts;
    struct s_token          *next;
   int                     n_args;
   t_redir                 *r;
   int                     r_count;
}   t_token;

/* =============================
 * Command & Redirection structures
 * ============================= */
typedef enum e_rtype
{
    R_IN,
    R_OUT_TRUNC,
    R_OUT_APPEND,
    R_HEREDOC
}   t_rtype;

typedef struct s_redir
{
    t_rtype type;
    char    *arg; /* filename or delimiter */
}   t_redir;

typedef struct s_cmd
{
    char    **argv;
    t_redir *r;
    int     r_count;
    int     is_builtin;
}   t_cmd;

typedef struct s_delim
{
    char *raw;
    char *clean;
    int   quoted;
}   t_delim;

typedef struct s_shell
{
    char            *input;
    char            **args;
    t_arr           *parsed_args;
    int             n_tokens;
    int             n_cmd;
    t_token         *tokens;
    t_list          *cmd_tail;
    t_list          *cmd_head;
    t_list          *env;
    int             fd_in;
    int             fd_out;
    t_arr           *bcmd;
    t_arr           *oper;
    pid_t           *pids;
    int             fd_pid[2];
    t_subtoken_container *heredoc;
    int             exit_status;
}   t_shell;

/* =============================
 * PROTOTYPES
 * ============================= */

/* prototypes manquants */
char    *replace_exit_code(const char *input, int exit_status);
char    *replace_variables(const char *input, t_shell *shell);
void    launch_process(t_shell *shell);

void free_cmd_list(t_shell *shell);

/* --- Core --- */
int     start_shell(t_shell *shell, char **envp);
void    init_minishell(t_shell *shell, char **envp);
int     looping(t_shell *shell);
void    free_minishell(t_shell *shell);
void    execute_command(t_shell *shell);
int     is_builtin(const char *cmd);
void    exit_shell(t_shell *shell, int exit_code);

/* --- Builtins --- */
/* --- Builtins (execution) --- */
void handle_cd(t_shell *shell);
void handle_exit(t_shell *shell);
void handle_env(t_shell *shell);
void handle_export(t_shell *shell);
void handle_unset(t_shell *shell);
void handle_echo(t_shell *shell);

/* --- Builtins (parser) --- */
int   builtin_echo(t_shell *shell, char **argv);
int   builtin_cd(t_shell *shell, char **argv);
int   builtin_export(t_shell *shell, char **argv);
int   builtin_env(t_shell *shell, char **argv);
int   builtin_exit(t_shell *shell, char **argv);
int builtin_pwd(t_shell *shell, char **argv);
int builtin_unset(t_shell *shell, char **argv);

int   export_no_arguments(t_shell *shell);
int   process_export_argument(char *arg, t_shell *shell);
/* --- Env --- */
char    *get_env_value(t_list *env, const char *name);
char    **list_to_envp(t_list *env);
int     env_len(t_list *env);
void    print_env(t_list *env);
t_list  *init_env(char **envp);
int     set_env_value(t_list **env, const char *key, const char *value);
char    *find_env_value(t_list *env, const char *key);

/* --- Parsing --- */
t_arr   *custom_split(const char *str, t_shell *shell);
int     count_tokens(t_shell *shell, t_arr *parsed_args, t_arr *oper);
void    attribute_token_type(t_shell *shell);
void    assign_redirs(t_shell *shell);
int     count_args_cmd(t_shell *shell, int i);
int     attribute_cmd_subtokens(t_shell *shell, t_token *cmd_token, int idx, int len);
int     count_subtokens(const char *str);
void    subtoken_of_cmd(t_subtoken_container *container, char *arg);
int     find_c_nonescaped(const char *str, char *needle, int size_needle);
bool    escape_check(const char *str, int idx);

//void    file_access_redirection(t_shell *shell, void **arr, int t_arr_index, int i);
void    build_cmd_list(t_shell *shell);
int     file_access_redirection(t_shell *shell, void **arr, int t_arr_index, int i);

char *find_command_path(char *cmd, t_list *env);
void     execute_cmd(t_shell *shell, t_token *cmd);
//void     ft_itoa_inplace(char *buf, int n);
char *ft_itoa_inplace(char *buf, int n);
void child_exit(char **args, char *cmd_path, char **envp, t_list *candidates, int code);

/* --- Utils --- */
size_t  t_arrlen(void **arr);
int     is_in_t_arr_str(t_arr *arr, const char *arg);
int     is_in_t_arr_dic_str(t_arr *arr, const char *arg);
void    build_t_arr_str(t_arr **dst, char **arr_str, int len);
void    init_all_t_arr(t_shell *shell);
void    free_tab(char **tab);
void    ft_free(void **thing);
void    init_signals(void);
void    handle_error(const char *message);

/* --- Listes --- */
t_list  *ft_lstnew(void *content);
void    ft_lstadd_back(t_list **lst, t_list *new);
void    ft_lstadd_front(t_list **lst, void *content);
t_list  *search_lst(t_list *lst, const char *target);
void    replace_or_add_env(t_list **env, const char *key, const char *value);
void    free_list_str(t_list *lst);
/* --- Listes & Chaînes --- */

//void    push_lst(t_list **lst, char *value);
void    push_lst(t_list **lst, void *content);

char    *ft_strdup_count(const char *src, int *count);

char    **expand_cmd(t_token *token, t_list *env);
int (*get_builtin_handler(t_arr *bcmd, int idx))(t_shell *, char **);

void free_str_array(char **arr);

/* --- Debug --- */
void    print_all_parts(t_shell *shell);
void    print_dic(t_arr *arr);

void free_tokens(t_shell *parser);
int ft_echo(t_shell *shell, char **argv);
int ft_cd(t_shell *shell, char **argv);
int ft_pwd(t_shell *shell, char **argv);
int ft_export(t_shell *shell, char **argv);
int ft_unset(t_shell *shell, char **argv);
int ft_env(t_shell *shell, char **argv);
int ft_exit(t_shell *shell, char **argv);
int handle_heredoc(t_shell *shell, char **argv);
int handle_append(t_shell *shell, char **argv);

int handle_and(t_shell *shell, char **argv);
int handle_or(t_shell *shell, char **argv);
int handle_pipe(t_shell *shell, char **argv);
int handle_redirect_in(t_shell *shell, char **argv);
int handle_redirect_out(t_shell *shell, char **argv);

typedef int (*builtin_fptr)(t_shell *, char **);

void free_t_arr_dic(t_arr *array);
/* ----- Redirection & heredoc ----- */
t_delim parse_delim(const char *raw);
char    *expand_vars_in_line(const char *line, t_shell *sh);
int     build_heredoc_fd(t_delim d, t_shell *sh);
int     apply_redirs_in_child(t_cmd *c, t_shell *sh);
void    child_exec_maillon(t_cmd *c, t_shell *sh, int i, int ncmd, int p[][2]);
# endif // MINISHELL_H
