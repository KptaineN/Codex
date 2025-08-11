//#include "../../include/minishell.h"

#include "export.h"
/*
static size_t env_count(t_shell *shell)
{
    size_t count = 0;
    t_env *env = shell->env;
    while (env)
    {
        count++;
        env = env->next;
    }
    return count;
}
// Libère partiellement le tableau d'entrées
static void free_entries(char **arr, size_t count)
{
    size_t i = 0;
    while (i < count)
    {
        free(arr[i]);
        i++;
    }
    free(arr);
}

// Crée une chaîne "KEY=VALUE" pour une entrée d'environnement
static char *create_env_entry(t_env *env)
{
    size_t klen = ft_strlen(env->key);
    size_t vlen = env->value ? ft_strlen(env->value) : 0;
    char *entry = malloc(klen + vlen + 2); // pour '=' et '\0'
    if (!entry)
        return NULL;
    ft_strcpy(entry, env->key);
    if (env->value)
    {
        entry[klen] = '=';
        ft_strcpy(entry + klen + 1, env->value);
    }
    else
    {
        entry[klen] = '\0';
    }
    return entry;
}

// Remplit un tableau de chaînes "KEY=VALUE"
static char **env_to_array(t_shell *shell)
{
    size_t n = env_count(shell);
    char **arr = malloc((n + 1) * sizeof(char *));
    if (!arr)
        return NULL;
    t_env *env_ptr = shell->env;
    size_t i = 0;
    while (env_ptr)
    {
        char *entry = create_env_entry(env_ptr);
        if (!entry)
        {
            free_entries(arr, i);
            return NULL;
        }
        arr[i++] = entry;
        env_ptr = env_ptr->next;
    }
    arr[i] = NULL;
    return arr;
}

static void print_export_arr(char **arr)
{
    size_t i = 0;
    while (arr[i])
    {
        char *eq = ft_strchr(arr[i], '=');
        if (!eq)
        {
            printf("༼⌐ ■ل͟■ ༽_/¯ %s\n", arr[i]);
        }
        else
        {
            *eq = '\0';
            printf(" (ಠ_ಠ)=ε/̵͇̿̿/'̿'̿-%s=\"%s\"\n", arr[i], eq + 1);
            *eq = '=';
        }
        i++;
    }
}

// Libère le tableau
static void free_export_arr(char **arr)
{
    size_t i = 0;
    while (arr[i])
    {
        free(arr[i]);
        i++;
    }
    free(arr);
}

// Vérifie si un nom de variable est valide
static int is_valid_identifier(const char *name)
{
    int i = 0;
    if (!name || !*name)
        return 0;
    
    // Doit commencer par une lettre ou underscore
    if (!ft_isalpha(*name) && *name != '_')
        return 0;
    
    // Le reste doit être alphanumérique ou underscore
    i = 1;
    while (name[i])
    {
        if (!ft_isalnum(name[i]) && name[i] != '_')
            return 0;
        i++;
    }
    return 1;
}

// Trouve une variable d'environnement
static t_env *find_env_var(t_shell *shell, const char *key)
{
    t_env *env = shell->env;
    while (env)
    {
        if (ft_strcmp(env->key, key) == 0)
            return env;
        env = env->next;
    }
    return NULL;
}
// Met à jour la valeur d'une variable d'environnement existante
static int update_env_var(t_env *env, const char *value)
{
    if (env->value)
        free(env->value);
    if (value)
        env->value = ft_strdup(value);
    else
        env->value = NULL;
    return 0;
}

// Crée une nouvelle variable d'environnement et l'ajoute à la liste du shell
static int create_env_var(t_shell *shell, const char *key, const char *value)
{
    t_env *new_env = malloc(sizeof(t_env));
    if (!new_env)
        return 1;
    
    new_env->key = ft_strdup(key);
    if (value)
        new_env->value = ft_strdup(value);
    else
        new_env->value = NULL;
    new_env->next = shell->env;
    shell->env = new_env;
    return 0;
}

// Ajoute ou modifie une variable d'environnement
static int set_env_var(t_shell *shell, const char *key, const char *value)
{
    t_env *existing = find_env_var(shell, key);
    
    if (existing)
        return update_env_var(existing, value);
    
    return create_env_var(shell, key, value);
}
// Traite un argument du format KEY=VALUE
static int handle_arg_with_assignment(char *arg, t_shell *shell)
{
    char *eq = ft_strchr(arg, '=');
    int ret = 0;

    if (eq)
    {
        // Temporarily split la chaîne en deux
        *eq = '\0';
        if (!is_valid_identifier(arg))
        {
            printf("minishell: export: `%s': not a valid identifier\n", arg);
            ret = 1;
        }
        else
        {
            if (set_env_var(shell, arg, eq + 1) != 0)
                ret = 1;
        }
        // Rétablit le '='
        *eq = '=';
    }
    return ret;
}

// Traite un argument contenant seulement la clé (KEY)
static int handle_arg_without_assignment(char *arg, t_shell *shell)
{
    int ret = 0;

    if (!is_valid_identifier(arg))
    {
        printf("minishell: export: `%s': not a valid identifier\n", arg);
        ret = 1;
    }
    else
    {
        t_env *existing = find_env_var(shell, arg);
        if (!existing)
        {
            if (set_env_var(shell, arg, NULL) != 0)
                ret = 1;
        }
    }
    return ret;
}
// Traite le cas où aucun argument n'est fourni
static int export_no_arguments(t_shell *shell)
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

// Traite un seul argument de l'export
static int process_export_argument(char *arg, t_shell *shell)
{
    if (ft_strchr(arg, '='))
        return handle_arg_with_assignment(arg, shell);
    else
        return handle_arg_without_assignment(arg, shell);
}*/

// builtin_export avec gestion des arguments, fracturé en sous-fonctions
/*int builtin_export(t_token *token, t_shell *shell)
{
    // Si pas d'arguments, affiche toutes les variables
    if (!token || !token->u.cmd_args_parts)
        return export_no_arguments(shell);
    
    int error = 0;
    int i = 1;
    while (token->u.cmd_args_parts[i])
    {
        error |= process_export_argument(token->u.cmd_args_parts[i], shell);
        i++;
    }
    shell->exit_status = error;
    return error;
}*/
/*int builtin_export(t_token *token, t_shell *shell)
{
	char **args = NULL;
	int arg_count = 0;
	int k = 0;

	// Compter le nombre total de sous-parties (arguments)
	for (int i = 0; token->u.cmd_args_parts[i].n_parts > 0; i++)
		arg_count += token->u.cmd_args_parts[i].n_parts;

	// Allouer le tableau d'arguments
	args = malloc(sizeof(char *) * (arg_count + 1));
	if (!args)
		return 1;

	// Copier chaque sous-token dans le tableau d'arguments
	for (int i = 0; token->u.cmd_args_parts[i].n_parts > 0; i++)
	{
		for (int j = 0; j < token->u.cmd_args_parts[i].n_parts; j++)
			args[k++] = ft_strdup(token->u.cmd_args_parts[i].parts[j].p);
	}
	args[k] = NULL;

	// Si aucun argument après "export", afficher l'environnement
	if (!args[1])
	{
		free_tab(args);
		return export_no_arguments(shell);
	}

	int error = 0;
	for (int i = 1; args[i]; i++)
		error |= process_export_argument(args[i], shell);

	free_tab(args);
	shell->exit_status = error;
	return error;
}*/
/*
int builtin_export(t_token *token, t_shell *shell)
{
    // Étape 1 : convertir cmd_args_parts en tableau de strings
    int total = 0;

    for (int i = 0; token->u.cmd_args_parts[i].n_parts > 0; i++)
        total += token->u.cmd_args_parts[i].n_parts;

    char **args = malloc(sizeof(char *) * (total + 2)); // +1 pour "export", +1 pour NULL
    if (!args)
        return (1);

    int k = 0;
    args[k++] = ft_strdup("export"); // Simuler args[0] = "export"

    for (int i = 0; token->u.cmd_args_parts[i].n_parts > 0; i++)
    {
        for (int j = 0; j < token->u.cmd_args_parts[i].n_parts; j++)
        {
            if (token->u.cmd_args_parts[i].parts[j].p)
                args[k++] = ft_strdup(token->u.cmd_args_parts[i].parts[j].p);
        }
    }
    args[k] = NULL;

    // Étape 2 : si aucun argument → afficher toutes les variables
    if (!args[1])
    {
        free_tab(args);
        return export_no_arguments(shell);
    }

    // Étape 3 : traiter les arguments
    int error = 0;
    for (int i = 1; args[i]; i++)
        error |= process_export_argument(args[i], shell);

    free_tab(args);
    shell->exit_status = error;
    return error;
}*/
void print_env_debug(t_list *env)
{
    while (env)
    {
        printf("[DEBUG] %s\n", (char*)env->content);
        env = env->next;
    }
}
int builtin_export(t_shell *shell, char **argv)
{
    // Cas sans argument explicite : export seul => affiche les variables exportées
    if (!argv[1])
        return export_no_arguments(shell);

    int error = 0;
    for (int i = 1; argv[i]; i++)
        error |= process_export_argument(argv[i], shell);

    shell->exit_status = error;
    return error;
}

/*/
int builtin_export(t_token *token, t_shell *shell)
{
    //print_env_debug(shell->env); // Debug: afficher l'environnement avant traitement

    if (!token || !token->cmd_args_parts)
        return export_no_arguments(shell);

    int total = 0;

    // Calculer le nombre total de sous-parties
    for (int i = 0; token->cmd_args_parts[i].n_parts > 0; i++)
        total += token->cmd_args_parts[i].n_parts;

    if (total == 0) // Aucun argument => affiche les exports
        return export_no_arguments(shell);

    char **args = malloc(sizeof(char *) * (total + 2)); // +1 pour "export", +1 pour NULL
    if (!args)
        return 1;

    int k = 0;
    args[k++] = ft_strdup("export"); // Simuler args[0]

    // Reconstruction des arguments
    for (int i = 0; token->cmd_args_parts[i].n_parts > 0; i++)
    {
        for (int j = 0; j < token->cmd_args_parts[i].n_parts; j++)
        {
            t_subtoken sub = token->cmd_args_parts[i].parts[j];
            if (sub.p && sub.len > 0)
                args[k++] = ft_strndup(sub.p, sub.len);
        }
    }
    args[k] = NULL;

    // Cas sans argument explicite après "export"
    if (!args[1])
    {
        free_str_array(args);
        return export_no_arguments(shell);
    }

    // Traiter les arguments
    int error = 0;
    for (int i = 1; args[i]; i++)
        error |= process_export_argument(args[i], shell);

    free_str_array(args);
    shell->exit_status = error;
    return error;
}*/
