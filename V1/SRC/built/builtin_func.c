/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_func.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiefer <nkiefer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 07:38:32 by eganassi          #+#    #+#             */
/*   Updated: 2025/08/13 15:33:45 by nkiefer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_echo(t_shell *shell, char **argv)
{
	return (builtin_echo(shell, argv));
}

int	ft_cd(t_shell *shell, char **argv)
{
	return (builtin_cd(shell, argv));
}

int	ft_pwd(t_shell *shell, char **argv)
{
	return (builtin_pwd(shell, argv));
}

int	ft_export(t_shell *shell, char **argv)
{
	return (builtin_export(shell, argv));
}

int	ft_unset(t_shell *shell, char **argv)
{
	return (builtin_unset(shell, argv));
}
