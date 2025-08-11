
#include "../../include/minishell.h"


// Remplace ou ajoute une variable
int set_env_value(t_list **env, const char *key, const char *value)
{
	t_list *tmp = *env;
	size_t key_len = ft_strlen(key);
	char *new_str;

	// Cherche si la clé existe déjà
	while (tmp)
	{
		char *content = (char *)tmp->content;
		char *equal = ft_strchr(content, '=');
		if (equal && (size_t)(equal - content) == key_len && !strncmp(content, key, key_len))
		{
			free(tmp->content);
			new_str = malloc(key_len + 1 + ft_strlen(value) + 1);
			if (!new_str) exit(1);
			sprintf(new_str, "%s=%s", key, value);
			tmp->content = new_str;
			return 0;
		}
		tmp = tmp->next;
	}
	// Sinon ajoute un noeud
	new_str = malloc(key_len + 1 + ft_strlen(value) + 1);
	if (!new_str) exit(1);
	sprintf(new_str, "%s=%s", key, value);
	t_list *node = malloc(sizeof(t_list));
	if (!node) exit(1);
	node->content = new_str;
	node->next = *env;
	*env = node;
	return 0;
}

char *get_env_value(t_list *env, const char *key)
{
    size_t key_len = ft_strlen(key);
    while (env)
    {
        char *content = env->content;
        char *equal = ft_strchr(content, '=');
        if (equal && (size_t)(equal - content) == key_len && !ft_strncmp(content, key, key_len))
            return equal + 1;
        env = env->next;
    }
    return NULL;
}



char	*get_value_env(t_list *env, char *value, int len)
{
	t_list	*temp;
	temp = env;
	while (1)
	{
		if (ft_strncmp(temp->content, value, len) == 0 && *(char* )(temp->content+len) == '=')
			return (temp->content + len +1); // Skip "value="
		temp = temp->next;
		if (temp == env)
			return (NULL);
	}
	return (NULL);
}

// Helper function to get PATH from environment
static char	*get_path_env(t_list *env)
{
	t_list	*temp;

	temp = env;
	while (1)
	{
		if (ft_strncmp(temp->content, "PATH=", 5) == 0)
			return (temp->content + 5); // Skip "PATH="
		temp = temp->next;
		if (temp == env)
			return (NULL);
	}
	return (NULL);
}

// Helper function to join path and command
static char	*join_path(char *dir, char *cmd)
{
	char	*full_path;
	int		dir_len;
	int		cmd_len;

	dir_len = ft_strlen(dir);
	cmd_len = ft_strlen(cmd);
	int i, j;
	full_path = malloc(dir_len + cmd_len + 2); // +2 for '/' and '\0'
	if (!full_path)
		return (NULL);
	// Copy directory
	i = 0;
	while (i < dir_len)
	{
		full_path[i] = dir[i];
		i++;
	}
	// Add separator
	full_path[i++] = '/';
	// Copy command
	j = 0;
	while (j < cmd_len)
	{
		full_path[i + j] = cmd[j];
		j++;
	}
	full_path[i + j] = '\0';
	return (full_path);
}

// Main function to find command path
char	*find_command_path(char *cmd, t_list *env)
{
	char	*path_env;
	char	*path_copy;
	char	*dir;
	char	*full_path;

	int i, start, len;
	// If command contains '/', it's already a path
	if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, F_OK | X_OK) == 0)
			return (ft_strdup(cmd));
		return (NULL);
	}
	// Get PATH envirnment variable
	path_env = get_path_env(env);
	if (!path_env)
		return (NULL);
	// Make a copy of PATH to work with
	len = ft_strlen(path_env);
	path_copy = malloc(len + 1);
	if (!path_copy)
		return (NULL);
	ft_strcpy(path_copy, path_env);
	// Search through each directory in PATH
	start = 0;
	i = 0;
	while (i <= len)
	{
		if (path_copy[i] == ':' || path_copy[i] == '\0')
		{
			path_copy[i] = '\0'; // Null-terminate current directory
			dir = path_copy + start;
			// Skip empty directories
			if (*dir != '\0')
			{
				full_path = join_path(dir, cmd);
				if (full_path && access(full_path, F_OK | X_OK) == 0)
				{
					free(path_copy);
					return (full_path);
				}
				if (full_path)
					free(full_path);
			}
			start = i + 1;
		}
		i++;
	}
	free(path_copy);
	return (NULL);
}


int count_exp_len(t_subtoken *b,int *k)
{
	int var_len = 0;
	if (ft_isalpha(b->p[*k + 1]) || b->p[*k + 1] == '_') {
        var_len = 1;
        while (*k + 1 + var_len < b->len &&
               (ft_isalnum(b->p[*k + 1 + var_len]) || b->p[*k + 1 + var_len] == '_')) {
            var_len++;
        }
	}
	return var_len;
}

void expand_variable(t_subtoken *b, int *k, t_list **curr, int *count, t_list *env)
{
    int var_len;
	var_len=count_exp_len(b,k);
	if (var_len>0)
	{
		char *value = get_value_env(env , (char *)&b->p[(*k)+1], var_len);
        push_lst(curr,ft_strdup_count (value,count));
		*k += var_len;
	}
}

void expand_str(t_subtoken *b, t_list *env, int *count, t_list **curr)
{
	int k = 0;
	while(k<b->len)
	{
		if (k < b->len && b->p[k] == '$') 
		{
			if (k + 1 == b->len || b->p[k + 1] == ' ') 
				push_lst(curr, ft_strdup_count("$", count));
			else if (b->p[k + 1] == '$')
			{
				push_lst(curr, ft_strdup(get_value_env(env,"PID",3)));
				k++;
			}
			else
				expand_variable(b, &k, curr, count,env); // Handles variable case	
		}
		else
			(*count)++;
		k++;
	}
}

char *build_expansion(t_subtoken_container *a,int count, t_list **add_head)
{
	t_list *head = *add_head;
	char *new = malloc(count+1);
	if (!new)
		perror("MALLOC build_expansion");
	int i = 0;	
	int j = 0;
	int k;
	t_subtoken *b;
	t_list *tmp;

	while(j<a->n_parts) // 
	{
		b = &a->parts[j];
		if (b->type == QUOTE_SINGLE) 	//no expansion
		{
			ft_strncpy(&new[i],b->p,b->len);
			i+=b->len;
		}
		else							//expansion
		{
			k = 0;
			while(k<b->len)
			{
				if (b->p[k] == '$')
				{
					ft_strcpy(&new[i],head->content);
					i+= ft_strlen(head->content);
					tmp = head;
					head = head->next;
					free(tmp->content);
					free(tmp);
					if (k+1<b->len && b->p[k+1] == '$')
						k++;
					else
						k+=count_exp_len(b,&k);
				}
				else
					new[i++] = b->p[k];
				k++;
			}
		}	
		j++;
	}
	new[i] = 0;
	return new;
}
char *expand_container(t_subtoken_container *a, t_list **head, t_list *env)
{
	(void)head;
    (void)env;
    if (!a || !a->parts || a->n_parts <= 0)
        return ft_strdup("");

    // On calcule la taille totale
    int total_len = 0;
    for (int i = 0; i < a->n_parts; i++)
        total_len += a->parts[i].len;

    char *out = malloc(total_len + 1);
    if (!out)
        return NULL;

    int pos = 0;
    for (int i = 0; i < a->n_parts; i++)
    {
        ft_memcpy(out + pos, a->parts[i].p, a->parts[i].len);
        pos += a->parts[i].len;
    }
    out[total_len] = 0;
    return out;
}


char **expand_cmd(t_token *token, t_list *env)
{
    if (!token || !token->cmd_args_parts)
        return NULL;

    int skip_first = 0;
    int nb_args = token->n_args;
    // Check si premier argument == commande (pour ne pas le doubler)
    if (nb_args > 0
        && token->cmd_args_parts[0].n_parts == 1
        && token->cmd_args_parts[0].parts[0].len == (int)ft_strlen(token->value)
        && ft_strncmp(token->cmd_args_parts[0].parts[0].p, token->value, token->cmd_args_parts[0].parts[0].len) == 0)
    {
        skip_first = 1;
    }

    int argc_final = skip_first ? nb_args : nb_args + 1;
    char **res = malloc(sizeof(char *) * (argc_final + 1));
    if (!res)
        return NULL;

    int j = 0;
    // Ajoute la commande au début si pas déjà là
    if (!skip_first)
        res[j++] = ft_strdup(token->value);

    // Ajoute les arguments (concaténation de sous-tokens si besoin)
    for (int i = 0; i < nb_args; i++)
        res[j++] = expand_container(&token->cmd_args_parts[i], NULL, env);

    res[j] = NULL;
    // DEBUG
   // for (int k = 0; k < j; k++)
        //printf("[expand_cmd] argv[%d] = '%s'\n", k, res[k]);

    return res;
}


int (*get_builtin_handler(t_arr *bcmd, int idx))(t_shell *, char **)
{
    if (!bcmd || idx < 0 || idx >= bcmd->len)
        return NULL;
    t_dic *dic = (t_dic *)bcmd->arr[idx];
    return dic->value;
}


/*
 * Exécute une commande, builtin ou externe, dans un processus enfant.
 */
void execute_cmd(t_shell *shell, t_token *cmd)
{
    char      **args;
    char       *cmd_path;
    char      **envp;

    if (!cmd || !cmd->value)
        child_exit(NULL, NULL, NULL, NULL, 1);

    // Expansion des arguments
    args = expand_cmd(cmd, shell->env);
    if (!args || !args[0])
    {
        fprintf(stderr, "%s: command not found\n", cmd->value);
        child_exit(args, NULL, NULL, NULL, 127);
    }

    /* 1) Built-ins */
    int idx = is_in_t_arr_str(shell->bcmd, args[0]);
    if (idx != -1)
    {
        int (*handler)(t_shell *, char **) = get_builtin_handler(shell->bcmd, idx);
        //printf("DEBUG handler=%p idx=%d\n", handler, idx);
		//printf("[CALL] handler=%p for %s\n", handler, args[0]);

		if (handler)
        {
            shell->exit_status = handler(shell, args);
            exit_shell(shell, shell->exit_status);
        }
        // En cas d’imprévu
        child_exit(args, NULL, NULL, NULL, 1);
    }

    /* 2) Recherche du PATH */
    cmd_path = find_command_path(args[0], shell->env);
    if (!cmd_path)
    {
        fprintf(stderr, "%s: command not found\n", args[0]);
        child_exit(args, NULL, NULL, NULL, 127);
    }

    /* 3) Préparation de l'envp et exec */
    envp = linked_to_array_string(shell->env);
    execve(cmd_path, args, envp);

    /* 4) Si execve échoue, afficher l’erreur et cleanup */
    perror("execve");
    child_exit(args, cmd_path, envp, NULL, 127);
}


