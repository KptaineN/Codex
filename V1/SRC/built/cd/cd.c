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
/**
 * cd -: Change to the previous directory. wrong comportemetn obseved
 * when using cd -: it should print the previous directory and change to it.
home/nkiefer/Documents/MINISHELL/c/MINI_Sh3LL/MINISHELL NRICO-NOE/obj
ᕕ( ᐛ )ᕗ minishell$ cd -
ᕕ( ᐛ )ᕗ minishell$ pwd
/home/nkiefer/Documents/MINISHELL/c/-
/MINI_Sh3LL/MINISHELL NRICO-NOE/minishell_tester
ᕕ( ᐛ )ᕗ minishell$


static int  cd_err(t_shell *sh, const char *msg)
{
    write(2, msg, ft_strlen(msg));
    sh->exit_status = 1;
    return (1);
}

static int  join_paths(char *dst, size_t cap,
                       const char *a, const char *b)
{
    size_t need;

    need = ft_strlen(a) + ft_strlen(b) + 1;
    if (need > cap)
        return (-1);
    ft_strlcpy(dst, a, cap);
    ft_strlcat(dst, b, cap);
    return (0);
}

static const char *env_or_err(t_shell *sh,
                              const char *key,
                              const char *errmsg)
{
    const char *v;

    v = sh_getenv(sh, key);
    if (!v)
    {
        cd_err(sh, errmsg);
        return (NULL);
    }
    return (v);
}



static const char *cd_tilde_home(t_shell *sh)
{
    return (env_or_err(sh, "HOME", "cd: HOME not set\n"));
}

static const char *cd_tilde_slash(t_shell *sh,
                                  const char *arg,
                                  char *buf)
{
    const char *home;

    home = cd_tilde_home(sh);
    if (!home)
        return (NULL);
    if (join_paths(buf, PATH_MAX, home, arg + 1) < 0)
        return (cd_err(sh, "cd: path too long\n"), NULL);
    return (buf);
}

static const char *cd_tilde_minus(t_shell *sh,
                                  const char *arg,
                                  char *buf,
                                  int *print_after)
{
    const char *oldp;

    oldp = env_or_err(sh, "OLDPWD", "cd: OLDPWD not set\n");
    if (!oldp)
        return (NULL);
    *print_after = 1;
    if (arg[2] == '/')
    {
        if (join_paths(buf, PATH_MAX, oldp, arg + 2) < 0)
            return (cd_err(sh, "cd: path too long\n"), NULL);
        return (buf);
    }
    return (oldp);
}

static const char *cd_tilde_plus(t_shell *sh,
                                 const char *arg,
                                 char *buf)
{
    const char  *pwd;

    pwd = sh_getenv(sh, "PWD");
    if (!pwd)
    {
        if (!getcwd(buf, PATH_MAX))
            return (perror("cd"), NULL);
        pwd = buf;
    }
    if (arg[2] == '/')
    {
        if (join_paths(buf, PATH_MAX, pwd, arg + 2) < 0)
            return (cd_err(sh, "cd: path too long\n"), NULL);
        return (buf);
    }
    return (pwd);
}

static const char *cd_expand_tilde(t_shell *sh,
                                   const char *arg,
                                   char *buf,
                                   int *print_after)
{
    if (arg[1] == '\0')
        return (cd_tilde_home(sh));
    if (arg[1] == '/')
        return (cd_tilde_slash(sh, arg, buf));
    if (arg[1] == '-' && (arg[2] == '\0' || arg[2] == '/'))
        return (cd_tilde_minus(sh, arg, buf, print_after));
    if (arg[1] == '+' && (arg[2] == '\0' || arg[2] == '/'))
        return (cd_tilde_plus(sh, arg, buf));
    
    return (arg);
}


static const char *cd_resolve_target(t_shell *sh,
                                     const char *arg,
                                     char *buf,
                                     int *print_after)
{
    if (!arg || *arg == '\0')
        return (cd_tilde_home(sh));
    if (ft_strcmp(arg, "-") == 0)
    {
        *print_after = 1;
        return (env_or_err(sh, "OLDPWD", "cd: OLDPWD not set\n"));
    }
    if (arg[0] == '~')
        return (cd_expand_tilde(sh, arg, buf, print_after));
    return (arg);
}


int     builtin_cd(t_shell *sh, char **args)
{
    char        old_pwd[PATH_MAX];
    char        new_pwd[PATH_MAX];
    char        buf[PATH_MAX];
    const char  *target;
    int         print_after;

    if (args[1] && args[2])
        return (cd_err(sh, "cd: too many arguments\n"));
    if (!getcwd(old_pwd, sizeof(old_pwd)))
        return (perror("cd"), sh->exit_status = 1);
    print_after = 0;
    target = cd_resolve_target(sh, args[1], buf, &print_after);
    if (!target)
        return (sh->exit_status = 1);
    if (chdir(target) != 0)
        return (perror("cd"), sh->exit_status = 1);
    if (!getcwd(new_pwd, sizeof(new_pwd)))
        return (perror("cd"), sh->exit_status = 1);
    set_env_value(&sh->env, "OLDPWD", old_pwd);
    set_env_value(&sh->env, "PWD", new_pwd);
    if (print_after)
        printf("%s\n", new_pwd);
    return (sh->exit_status = 0);
}
}*/
