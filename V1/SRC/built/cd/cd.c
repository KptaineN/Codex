/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiefer <nkiefer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 16:35:57 by eganassi          #+#    #+#             */
/*   Updated: 2025/08/13 22:05:16 by nkiefer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cd.h"

static int	cd_too_many(char **args, t_shell *sh)
{
	if (args[1] && args[2])
	{
		ft_putstr_fd("(;・_・)՞minishell: cd: too many arguments\n", 2);
		sh->exit_status = 1;
		return (1);
	}
	return (0);
}

static const char	*cd_pick_target(char **args)
{
	if (args[1] == NULL || *args[1] == '\0')
		return (getenv("HOME"));
	if (ft_strcmp(args[1], "-") == 0 || ft_strcmp(args[1], "--") == 0)
		return (getenv("OLDPWD"));
	return (args[1]);
}

static int	cd_switch_to(const char *target, t_shell *sh)
{
	if (!target)
	{
		ft_putstr_fd("minishell: cd: HOME/OLDPWD not set\n", 2);
		sh->exit_status = 1;
		return (0);
	}
	if (chdir(target) != 0)
	{
		perror("cd");
		sh->exit_status = 1;
		return (0);
	}
	return (1);
}

static int	cd_update_pwds(t_shell *sh, const char *old_pwd)
{
	char	new_pwd[4096];

	if (!getcwd(new_pwd, 4096))
	{
		perror("cd");
		sh->exit_status = 1;
		return (0);
	}
	set_env_value((t_list **)&sh->env, "OLDPWD", (char *)old_pwd);
	set_env_value((t_list **)&sh->env, "PWD", new_pwd);
	sh->exit_status = 0;
	return (1);
}

int	builtin_cd(t_shell *sh, char **args)
{
	char		old_pwd[4096];
	const char	*target;

	if (cd_too_many(args, sh))
		return (sh->exit_status);
	if (!getcwd(old_pwd, 4096))
	{
		perror("cd");
		sh->exit_status = 1;
		return (sh->exit_status);
	}
	target = cd_pick_target(args);
	if (!cd_switch_to(target, sh))
		return (sh->exit_status);
	if (!cd_update_pwds(sh, old_pwd))
		return (sh->exit_status);
	return (sh->exit_status);
}
