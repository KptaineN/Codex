#include "export.h"

/*
 * The environment list stores entries as simple strings of the form
 * "KEY=VALUE".  The previous implementation assumed a dedicated structure
 * which led to invalid memory access and segmentation faults when handling
 * valid identifiers.  The helpers below operate directly on the string
 * representation to safely add, update and search variables.
 */

static char *build_entry(const char *key, const char *value)
{
    char    *tmp;
    char    *entry;

    tmp = ft_strjoin(key, "=");
    if (!tmp)
        return NULL;
    if (value)
    {
        entry = ft_strjoin(tmp, value);
        free(tmp);
    }
    else
        entry = tmp; // already "key="
    return entry;
}

t_list *find_env_var(t_shell *shell, const char *key)
{
    t_list  *node;
    size_t  key_len;

    key_len = ft_strlen(key);
    node = shell->env;
    while (node)
    {
        char    *entry;
        char    *eq;
        size_t  entry_len;

        entry = (char *)node->content;
        eq = ft_strchr(entry, '=');
        entry_len = eq ? (size_t)(eq - entry) : ft_strlen(entry);
        if (entry_len == key_len && ft_strncmp(entry, key, key_len) == 0)
            return node;
        node = node->next;
    }
    return NULL;
}

int update_env_var(t_list *env_node, const char *value)
{
    char    *entry;
    char    *eq;
    char    *key;
    char    *new_entry;

    entry = (char *)env_node->content;
    eq = ft_strchr(entry, '=');
    if (eq)
        key = ft_substr(entry, 0, eq - entry);
    else
        key = ft_strdup(entry);
    if (!key)
        return 1;
    free(entry);
    new_entry = build_entry(key, value);
    free(key);
    if (!new_entry)
        return 1;
    env_node->content = new_entry;
    return 0;
}

int create_env_var(t_shell *shell, const char *key, const char *value)
{
    t_list  *new_node;
    char    *entry;

    entry = build_entry(key, value);
    if (!entry)
        return 1;
    new_node = malloc(sizeof(*new_node));
    if (!new_node)
    {
        free(entry);
        return 1;
    }
    new_node->content = entry;
    new_node->next = shell->env;
    shell->env = new_node;
    return 0;
}

int set_env_var(t_shell *shell, const char *key, const char *value)
{
    t_list *existing;

    existing = find_env_var(shell, key);
    if (existing)
        return update_env_var(existing, value);
    return create_env_var(shell, key, value);
}

