/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launcher.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiefer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 16:28:02 by nkiefer           #+#    #+#             */
/*   Updated: 2025/08/16 16:28:04 by nkiefer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LAUNCHER_H
# define LAUNCHER_H

#include "minishell.h"

typedef struct s_exec_ctx
{
        t_shell *sh;
        t_list  *node;
        int     i;
        int     prev_fd;
        int     pipe_fd[2];
}       t_exec_ctx;

int     run_single_builtin_if_alone(t_shell *sh);
int     check_pipe(t_exec_ctx *c);
void    child_setup_fds(t_exec_ctx *c);
void    child_exec(t_exec_ctx *c);
void    parent_after_fork(t_exec_ctx *c, pid_t pid);
void    wait_all_update_status(t_shell *sh);
void    update_last_pid_env(t_shell *sh);
void    launch_process(t_shell *sh);
ssize_t read_pid_exact(int fd, pid_t *out);
void    set_env_pid(t_shell *shell, pid_t pid);
void    add_pid_env(t_shell *shell, int fd);
t_list  *find_env_entry(t_list *env, const char *key);
char    *build_kv_string(const char *key, const char *value);
void    replace_or_add_env(t_list **env, const char *key,
                                const char *value);
char    *ft_itoa_inplace(char *s, int n);

#endif // LAUNCHER_H

