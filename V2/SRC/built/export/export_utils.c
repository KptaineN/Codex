#include "export.h"

size_t env_count(t_shell *shell)
{
    size_t count = 0;
    t_list *current = shell->env;  // shell->parser.env est t_list *
    
    while (current)
    {
        count++;
        current = current->next;
    }
    return count;
}

// Si tu stockes des char* dans content
char *create_env_entry(char *env_line)
{
    return ft_strdup(env_line);
}

/**
char *create_env_entry(t_list *env)
{
    size_t klen = ft_strlen(env->key);
    size_t vlen = env->value ? ft_strlen(env->value) : 0;
    char *entry = malloc(klen + vlen + 2);
    if (!entry) return NULL;

    ft_strcpy(entry, env->key);
    if (env->value)
    {
        entry[klen] = '=';
        ft_strcpy(entry + klen + 1, env->value);
    }
    else entry[klen] = '\0';

    return entry;
}**/

char **env_to_array(t_shell *shell)
{
    size_t n = env_count(shell);
    char **arr = malloc((n + 1) * sizeof(char *));
    if (!arr) return NULL;

    size_t i = 0;
    for (t_list *node = shell->env; node; node = node->next)
    {
        t_list *env = (t_list *)node->content;
        arr[i] = create_env_entry((char*)env->content);
        if (!arr[i])
        {
            free_export_arr(arr);
            return NULL;
        }
        i++;
    }
    arr[i] = NULL;
    return arr;
}

void print_export_arr(char **arr)
{
    for (size_t i = 0; arr[i]; i++)
    {
        char *eq = ft_strchr(arr[i], '=');
        if (!eq)
            printf("༼⌐ ■ل͟■ ༽_/¯ %s\n", arr[i]);
        else
        {
            *eq = '\0';
            printf(" (ಠ_ಠ)=ε/̵͇̿̿/'̿'̿-%s=\"%s\"\n", arr[i], eq + 1);
            *eq = '=';
        }
    }
}

void free_export_arr(char **arr)
{
    for (size_t i = 0; arr[i]; i++)
        free(arr[i]);
    free(arr);
}

int export_no_arguments(t_shell *shell)
{
    char **arr = env_to_array(shell);
    if (!arr)
    {
        shell->exit_status = 1;
        return 1;
    }

    ft_bubble_str_sort(arr);
    print_export_arr(arr);
    free_export_arr(arr);
    shell->exit_status = 0;
    return 0;
}
