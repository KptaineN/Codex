/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_func.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiefer <nkiefer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 07:38:32 by eganassi          #+#    #+#             */
/*   Updated: 2025/07/28 13:28:33 by nkiefer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int ft_echo(t_shell *shell, char **argv)
{
    return builtin_echo(shell, argv);
}

int ft_cd(t_shell *shell, char **argv)
{

    return builtin_cd(shell, argv);
}
int ft_pwd(t_shell *shell, char **argv)
{
    return builtin_pwd(shell, argv);
}

int ft_export(t_shell *shell, char **argv)
{

    return builtin_export(shell, argv);
}

int ft_unset(t_shell *shell, char **argv)
{
    return builtin_unset(shell, argv);
}

int ft_env(t_shell *shell, char **argv)
{
    return builtin_env(shell, argv);
}

int ft_exit(t_shell *shell, char **argv)
{
    return builtin_exit(shell, argv);
}
//typedef int (*builtin_fptr)(t_shell *, char **); meme chose 
//t_dic *make_dic(const char *name, int (*fn)(t_shell *, char **))


