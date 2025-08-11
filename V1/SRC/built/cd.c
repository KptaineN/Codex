/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiefer <nkiefer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 16:35:57 by eganassi          #+#    #+#             */
/*   Updated: 2025/08/11 13:41:47 by nkiefer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*    first test
int builtin_cd(char **args, t_shell *shell)
{
    (void)shell;
	if (!args[1])
		return (chdir(getenv("HOME")));

	if (chdir(args[1]) != 0)
	{		if (errno == ENOENT)
			fprintf(stderr, "cd: no such file or directory: %s\n", args[1]);
		else if (errno == EACCES)
			fprintf(stderr, "cd: permission denied: %s\n", args[1]);
		else
		perror("cd");
		return (1);
	}
	// Optionnel : mettre à jour PWD dans shell->env
	return (0);
}*/
/*
// Recherche un nœud existant
static t_env *find_env_node(t_env *env, const char *key)
{
    while (env)
    {
        if (ft_strcmp(env->key, key) == 0)
            return env;
        env = env->next;
    }
    return NULL;
}*/
/**
// Ajoute un nouveau nœud en tête
static int add_env_node(t_list **env, const char *key, const char *value)
{
    t_list *node = malloc(sizeof(*node));
    if (!node) return -1;
    node->key   = ft_strdup(key);
    node->value = ft_strdup(value);
    if (!node->key || !node->value)
    {
        free(node->key);
        free(node->value);
        free(node);
        return -1;
    }
    node->next = *env;
    *env       = node;
    return 0;
}

// Met à jour ou crée la variable `key` à la valeur `value`
static int update_env(t_list **env, const char *key, const char *value)
{
	// Utilisation d'un pointeur vers pointeur pour parcourir la liste
	t_list **curr = env;
	while (*curr)
	{
		if (ft_strcmp((*curr)->key, key) == 0)
		{
			char *dup_val = ft_strdup(value);
			if (!dup_val)
				return -1;
			free((*curr)->value);
			(*curr)->value = dup_val;
			return 0;
		}
		curr = &(*curr)->next;
	}
	// Si non trouvé, on ajoute un nouveau nœud
	return add_env_node(env, key, value);
}

** Étapes du builtin cd ***

// 1) Sauvegarde l’ancien répertoire dans old_pwd
static int cd_save_oldpwd(char *old_pwd, size_t sz)
{
    if (!getcwd(old_pwd, sz))
    {
        perror("cd");
        return -1;
    }
    return 0;
}

// 2) Choisit la cible en fonction de args[1]
static const char *cd_choose_target(char **args, t_shell *shell)
{
	(void)shell;
    if (!args[1] || *args[1] == '\0')
        return getenv("HOME");
    if (ft_strcmp(args[1], "-") == 0)
        return getenv("OLDPWD");
    return args[1];
}

// 3) Change de répertoire
static int cd_do_chdir(const char *target)
{
    if (chdir(target) != 0)
    {
        perror("cd");
        return -1;
    }
    return 0;
}

// 4) Récupère le nouveau répertoire dans new_pwd
static int cd_save_newpwd(char *new_pwd, size_t sz)
{
    if (!getcwd(new_pwd, sz))
    {
        perror("cd");
        return -1;
    }
    return 0;
}

** Orchestrateur ***
int builtin_cd(char **args, t_shell *shell)
{
    char        old_pwd[4096];   // Taille PATH_MAX
    char        new_pwd[4096];
    const char *target;

    if (cd_save_oldpwd(old_pwd, sizeof(old_pwd)) < 0)
        return (shell->exit_status = 1);

    target = cd_choose_target(args, shell);
    if (!target)
    {
        errno = ENOENT; // Simule l'absence de HOME/OLDPWD
        perror("cd: HOME/OLDPWD not set");
        return (shell->exit_status = 1);
    }
    if (cd_do_chdir(target) < 0)
        return (shell->exit_status = 1);

    if (cd_save_newpwd(new_pwd, sizeof(new_pwd)) < 0)
        return (shell->exit_status = 1);

    if (update_env((t_list **)&shell->parser.env, "OLDPWD", old_pwd) < 0 ||
        update_env((t_list **)&shell->parser.env, "PWD",     new_pwd) < 0)
    {
        perror("cd");
        return (shell->exit_status = 1);
    }
    return (shell->exit_status = 0);
}*/
int builtin_cd(t_shell *shell, char **args)
{
    char old_pwd[4096];
    char new_pwd[4096];
    const char *target;

    if (!getcwd(old_pwd, sizeof(old_pwd)))
        return perror("cd"), shell->exit_status = 1;

    target = (args[1] == NULL || *args[1] == '\0') ? getenv("HOME") :
              (ft_strcmp(args[1], "-") == 0 ? getenv("OLDPWD") : args[1]);

    if (!target)
        return perror("cd: HOME/OLDPWD not set"), shell->exit_status = 1;
    if (chdir(target) != 0)
        return perror("cd"), shell->exit_status = 1;
    if (!getcwd(new_pwd, sizeof(new_pwd)))
        return perror("cd"), shell->exit_status = 1;

    set_env_value((t_list **)&shell->env, "OLDPWD", old_pwd);
    set_env_value((t_list **)&shell->env, "PWD", new_pwd);

    return (shell->exit_status = 0);
}


int builtin_pwd(t_shell *shell, char **argv)
{
    (void)shell; // On n'utilise pas shell ici
    (void)argv;
    char cwd[1024];
    
	if (getcwd(cwd, sizeof(cwd)))
	{
		printf("%s\n", cwd);
		return (0);
	}
	perror("pwd");
	return (1);
}