#ifndef EXPORT_H
#define EXPORT_H

#include "../../../include/minishell.h"

int builtin_export(t_shell *shell, char **argv);

/* export_args.c */
int process_export_argument(char *arg, t_shell *shell);

/* export_utils.c */
int export_no_arguments(t_shell *shell);

/* export_env.c */
t_list *find_env_var(t_shell *shell, const char *key);
int update_env_var(t_list *env, const char *value);
int create_env_var(t_shell *shell, const char *key, const char *value);
int set_env_var(t_shell *shell, const char *key, const char *value);

#endif
