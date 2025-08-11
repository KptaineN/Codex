#include "../../include/minishell.h"


/*
char **env_to_envp(t_env *env)
{
	int count = env_len(env); // à coder si besoin
	char **envp = malloc(sizeof(char *) * (count + 1));
	int i = 0;

	while (env)
	{
		envp[i] = ft_strjoin_3(env->key, "=", env->value); // "VAR=VALUE"
		if (!envp[i])
			return (NULL); // gestion à améliorer
		env = env->next;
		i++;
	}
	envp[i] = NULL;
	return envp;
}
char **env_to_envp(t_env *env)
{
	int count = env_len(env);
	char **envp = malloc(sizeof(char *) * (count + 1));
	int i = 0;

	if (!envp)
		handle_error("malloc");

	while (env)
	{
		envp[i] = ft_strjoin3(env->key, "=", env->value, 1); // "VAR=VALUE"
		if (!envp[i])
		{
			// libère les précédents
			while (--i >= 0)
				free(envp[i]);
			free(envp);
			return (NULL);
		}
		env = env->next;
		i++;
	}
	envp[i] = NULL;
	return envp;
}



void print_env(t_env *env)
{
    while (env)
    {
        printf("%s=%s\n", env->key, env->value);
        env = env->next;
    }
}
*/

int builtin_env(t_shell *shell, char **args)
{
    (void)args;
    t_list *cur = shell->env;
    while (cur)
    {
        t_env *env = cur->content;
        if (env->value)
            printf("%s=%s\n", env->key, env->value);
        cur = cur->next;
    }
    shell->exit_status = 0;
    return 0;
}
