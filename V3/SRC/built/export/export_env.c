#include "export.h"
typedef struct s_env
{
    char *key;
    char *value;
} t_env;

t_list *find_env_var(t_shell *shell, const char *key)
{
    for (t_list *node = shell->env; node; node = node->next)
    {
        t_env *env = (t_env *)node->content;
        if (ft_strcmp(env->key, key) == 0)
            return node;
    }
    return NULL;
}

int update_env_var(t_list *env_node, const char *value)
{
    t_env *env = (t_env *)env_node->content;
    free(env->value);
    if (value != NULL)
        env->value = ft_strdup(value);
    else
        env->value = NULL;
    return 0;
}

int create_env_var(t_shell *shell, const char *key, const char *value)
{
    t_env *new_env = malloc(sizeof(*new_env));
    if (new_env == NULL)
        return 1;

    new_env->key = ft_strdup(key);
    if (value != NULL)
        new_env->value = ft_strdup(value);
    else
        new_env->value = NULL;

    t_list *new_node = malloc(sizeof(*new_node));
    if (new_node == NULL)
    {
        free(new_env->key);
        free(new_env->value);
        free(new_env);
        return 1;
    }
    new_node->content = new_env;
    new_node->next = shell->env;
    shell->env = new_node;
    return 0;
}

int set_env_var(t_shell *shell, const char *key, const char *value)
{
    t_list *existing = find_env_var(shell, key);

    if (existing)
        return update_env_var(existing, value);
    else
        return create_env_var(shell, key, value);
}
