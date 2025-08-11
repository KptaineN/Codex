
#include "../../include/minishell.h"


// Helper function to get PATH from environment
char	*get_value_env(t_list *env, char *value, int len)
{
	t_list	*temp;
	temp = env;
	while (1)
	{
		if (strncmp(temp->content, value, len) == 0 && *(char* )(temp->content+len) == '=')
			return (temp->content + len +1); // Skip "value="
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

	dir_len = strlen(dir);
	cmd_len = strlen(cmd);
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
	if (strchr(cmd, '/'))
	{
		if (access(cmd, F_OK | X_OK) == 0)
			return (strdup(cmd));
		return (NULL);
	}
	// Get PATH envirnment variable
	path_env = get_value_env(env, "PATH", 4);
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
	if (isalpha(b->p[*k + 1]) || b->p[*k + 1] == '_') {
        var_len = 1;
        while (*k + 1 + var_len < b->len &&
               (isalnum(b->p[*k + 1 + var_len]) || b->p[*k + 1 + var_len] == '_')) {
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
				push_lst(curr,strdup(get_value_env(env,"PID",3)));
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
			strncpy(&new[i],b->p,b->len);
			i+=b->len;
		}
		else							//expansion
		{
			k = 0;
			while(k<b->len)
			{
				if (b->p[k] == '$')
				{
					strcpy(&new[i],head->content);
					i+=strlen(head->content);
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
	t_list *curr = *head;
	int j = 0;
	t_subtoken *b;
	int count = 0;
	//char *arr_str = malloc(sizeof(char *)*a->n_parts);
	while(j<a->n_parts) // 
	{
		b = &a->parts[j];
		if (b->type == QUOTE_SINGLE) 	//no expansion
			count+=b->len;
		else							//expansion
			expand_str(b,env,&count,&curr);
		//if (curr && (curr)->content)
		//	printf("%s\n", (char *)(curr)->content);
		j++;
	}
	return build_expansion(a,count,&((*head)->next));
}


char **expand_cmd(t_token *token, t_list *env)
{
	int i;
	t_subtoken_container *a;
	t_list *head = ft_lstnew(NULL);
	char **res = malloc(sizeof(char *)*(token->n_parts)); //omits first
	if (!res)
		perror("MALLOC expand_cmd");


	// input "hello"a 'mom' 
	// {"hello"a}, {mom} container
	// {hello,a}, {mom} subtoken
	// {h,e,l,l,o} char * 
	i = 0;
	while(i<token->n_parts) // container
	{
		a = &token->cmd_args_parts[i];
		res[i] = expand_container(a,&head,env); 
		//printf("%s\n", res[i]);
		i++;
	}
	res[i] = NULL;
	return res;
}



void execute(t_shell *shell, t_token *cmd)
{
	char **args = expand_cmd(cmd,shell->env);
	//char **env = linked_to_array_string(shell->env);
	if (!args)
		perror("malloc res and env execute()");
	execv(find_command_path(cmd->value,shell->env), (char **const) args);
}