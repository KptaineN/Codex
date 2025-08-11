#include "../../include/minishell.h"

int	is_numeric(const char *str)
{
	int	i = 0;

	if (!str || !str[0])
		return (0);
	if (str[0] == '+' || str[0] == '-')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
        return (1);
}

static char *strip_quotes(char *s)
{
    char *res;
    int i = 0;
    int j = 0;

    if (!s)
        return (NULL);
    res = malloc(ft_strlen(s) + 1);
    if (!res)
        return (NULL);
    while (s[i])
    {
        if (s[i] != '\'' && s[i] != '"')
            res[j++] = s[i];
        i++;
    }
    res[j] = '\0';
    return (res);
}

int builtin_exit(t_shell *shell, char **argv)
{
    long code = 0;
    char *arg;

    write(1, "exit\n", 5);

    if (argv[1])
    {
        arg = strip_quotes(argv[1]);
        if (!is_numeric(arg))
        {
            free(arg);
            ft_putstr_fd("minishell: exit: numeric argument required\n", 2);
            shell->exit_status = 2;
            exit_shell(shell, 2);
        }
        if (argv[2])
        {
            free(arg);
            ft_putstr_fd("minishell: exit: too many arguments\n", 2);
            shell->exit_status = 1;
            return (1);
        }
        code = ft_atoi(arg);
        free(arg);
        shell->exit_status = code % 256;
        exit_shell(shell, shell->exit_status);
    }
    shell->exit_status = 0;
    exit_shell(shell, 0);
    return (0);
}


char	*replace_exit_code(const char *input, int code)
{
	char	*res = ft_strdup(input);
	char	*pos;
	char	*code_str = ft_itoa(code);

	while ((pos = ft_strnstr(res, "$?", ft_strlen(res))))
	{
		*pos = '\0';
		char *before = ft_strdup(res);
		char *after = ft_strdup(pos + 2);
		char *tmp = ft_strjoin(before, code_str);
		char *new_res = ft_strjoin(tmp, after);
		free(res);
		free(before);
		free(after);
		free(tmp);
		res = new_res;
	}
	free(code_str);
	return (res);
}

/*
char	*replace_exit_code(const char *input, int exit_code)
{
	char	*result;
	char	*code_str;
	char	*pos;

	if (!input)
		return (NULL);
	code_str = ft_itoa(exit_code);
	pos = ft_strnstr(input, "$?", ft_strlen(input));
	if (!pos)
	{
		free(code_str);
		return (ft_strdup(input));
	}

	// Allocation : ancienne taille - 2 (pour "$?") + taille de code_str + 1
	size_t new_len = ft_strlen(input) - 2 + ft_strlen(code_str) + 1;
	result = malloc(new_len);
	if (!result)
	{
		free(code_str);
		return (NULL);
	}

	// Construction du résultat
	size_t prefix_len = pos - input;
	ft_strlcpy(result, input, prefix_len + 1); // copie jusqu’à "$?"
	ft_strlcat(result, code_str, new_len);
	ft_strlcat(result, pos + 2, new_len);

	free(code_str);
	return (result);
}
char	*replace_exit_code(const char *input, int exit_code)
{
	char	*code_str = ft_itoa(exit_code);
	char	*result;
	char	*tmp;
	char	*pos;

	if (!input || !code_str)
		return (NULL);
	tmp = ft_strdup(input);
	if (!tmp)
	{
		free(code_str);
		return (NULL);
	}

	pos = ft_strnstr(tmp, "$?", ft_strlen(tmp));
	while (pos)
	{
		*pos = '\0';
		char *joined = ft_strjoin(tmp, code_str);
		char *rest = ft_strdup(pos + 2);
		result = ft_strjoin(joined, rest);
		free(tmp);
		free(joined);
		free(rest);
		tmp = result;
		pos = ft_strnstr(tmp, "$?", ft_strlen(tmp));
	}
	free(code_str);
	return (tmp);
}*/
/*

#include <limits.h>   // pour PATH_MAX
#include <unistd.h>   // pour chdir(), getcwd()
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

// Prototype d’une fonction utilitaire à écrire :
//   si la clé existe, remplace sa valeur, sinon l’ajoute.
// Tu peux l’appeler update_env(shell->env, key, value);
int update_env_var(t_env **env, const char *key, const char *value)
{
    t_env *node = *env;

    // Cherche la clé existante
    while (node)
    {
        if (strcmp(node->key, key) == 0)
        {
            // remplace sans leak
            free(node->value);
            node->value = strdup(value);
            return (node->value ? 0 : -1);
        }
        node = node->next;
    }

    // Si pas trouvée, on ajoute en tête
    t_env *new = malloc(sizeof(*new));
    if (!new) return -1;
    new->key   = strdup(key);
    new->value = strdup(value);
    if (!new->key || !new->value)
    {
        free(new->key);
        free(new->value);
        free(new);
        return -1;
    }
    new->next = *env;
    *env      = new;
    return 0;
}


int builtin_cd(char **args, t_shell *shell)
{
    char old_pwd[PATH_MAX];
    char new_pwd[PATH_MAX];
    char *target;

    // 1) Ancien PWD
    if (getcwd(old_pwd, sizeof(old_pwd)) == NULL)
    {
        perror("getcwd");
        shell->exit_status = 1;
        return 1;
    }

    // 2) Choix du répertoire cible
    if (!args[1] || args[1][0] == '\0')
        target = getenv("HOME");  // ou find_env_value(shell->env, "HOME")
    else if (strcmp(args[1], "-") == 0)
        target = getenv("OLDPWD"); // idem : à récupérer dans shell->env
    else
        target = args[1];

    if (!target)
    {
        fprintf(stderr, "cd: HOME not set\n");
        shell->exit_status = 1;
        return 1;
    }

    // 3) Changement
    if (chdir(target) != 0)
    {
        if (errno == ENOENT)
            fprintf(stderr, "cd: no such file or directory: %s\n", target);
        else if (errno == EACCES)
            fprintf(stderr, "cd: permission denied: %s\n", target);
        else
            perror("cd");
        shell->exit_status = 1;
        return 1;
    }

    // 4) Nouveau PWD
    if (getcwd(new_pwd, sizeof(new_pwd)) == NULL)
    {
        perror("getcwd");
        shell->exit_status = 1;
        return 1;
    }

    // 5) Mettre à jour OLDPWD puis PWD dans l’env de minishell
    update_env_var(&shell->env, "OLDPWD", old_pwd);
    update_env_var(&shell->env, "PWD",     new_pwd);

    shell->exit_status = 0;
    return 0;
}*/
