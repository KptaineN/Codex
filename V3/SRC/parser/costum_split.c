

#include "../../include/minishell.h"

// normal strdup - get rid of later when LIBFT
char *ft_strdup(const char *s1)
{
    char *dup;
    int len;
    int i;

    if (!s1)
        return (NULL);
    
    len = 0;
    while (s1[len])
        len++;
    
    dup = malloc(sizeof(char) * (len + 1));
    if (!dup)
        return (NULL);
    
    i = 0;
    while (i < len)
    {
        dup[i] = s1[i];
        i++;
    }
    dup[i] = '\0';
    
    return (dup);
}

/* Cette fonciton sert a une partie importante de minishell
essaye echo "hello
*/
bool escape_check(const char *str ,int idx)
{
	bool i = 1;
	if (idx != 0)
	{
		idx--;
		while(idx != 0 && str[idx] =='\\')
		{	i^=1;
			idx--;
		}
		if (i)
			return 1;
		return 0;
	}
	return 1;
}

/*
compte le nombre argument pour les commandes shell
ex: "ls -la > grep "Noe!" file.txt"
-> "ls" "-la" ">" "grep" "\"Noe!\"" "file.txt"

gere les cas ou: "\"hello\'mamman\'\"" -> "hello\'mamman\'" (expansion apres pour toi)
*/
static int	count_arg(const char *str, t_shell *shell)//, int *sub_n)
{
	int		count;
	bool	in_single_quote;
	bool	in_double_quote;
	bool	in_word;
	int idx_oper;
	//t_quote_type current_quote = QUOTE_NONE;
	
	count = 0;
	in_single_quote = false;
	in_double_quote = false;
	in_word = false;
	int i = 0;
	while(str[i])
	{
		char c = str[i];
		(void) c;
		idx_oper = is_in_t_arr_dic_str(shell->oper, (char *)&str[i]);
		if (str[i] == '\'' && !in_double_quote && escape_check(str,i))
			in_single_quote = !in_single_quote;
		else if (str[i] == '"' && !in_single_quote && escape_check(str,i))
			in_double_quote = !in_double_quote;	
		else if (str[i] == ' ' && !in_single_quote && !in_double_quote)
		{
			if (in_word)
			{
				in_word = false;
				count++;
			}
		}
		else if (idx_oper != -1 && !in_single_quote && !in_double_quote)
		{						// is a oper
			in_word = false;
			count++;
			i+=strlen((char *)((t_dic *)shell->oper->arr[idx_oper])->key)-1;
		}
		else if (!in_word)
		{	
			in_word = true;
		}
		i++;
	}
	if (in_word)
		count++;
	return (count);
}

// Function to extract a single token
static char	*extract_arg(const char *str, int *start, t_shell *shell)
{
	bool	in_single_quote;
	bool	in_double_quote;
	int		token_start;
	int		token_end;
	int		token_len;
	char	*token;

	int idx_oper_one;
	int oper_ad = 0;

	in_single_quote = false;
	in_double_quote = false;
	token_start = *start;
	token_end = *start;
	// Skip leading spaces
	while (str[token_start] && str[token_start] == ' ')
		token_start++;
	if (!str[token_start])
		return (NULL);
	token_end = token_start;
	// Find the end of the token
	
	while (str[token_end])
	{	
		char c = str[token_end];
		if (str[token_end] == '\'' && !in_double_quote && escape_check(str,token_end))
			in_single_quote = !in_single_quote;
		else if (str[token_end] == '"' && !in_single_quote && escape_check(str,token_end))
			in_double_quote = !in_double_quote;
		else if (!in_single_quote && !in_double_quote)
		{
			if (str[token_end] == ' ')
				break ;
			idx_oper_one = is_in_t_arr_dic_str(shell->oper, &str[token_end]);
			if (idx_oper_one != -1)
			{	
				oper_ad = strlen((const char *)((t_dic *)shell->oper->arr[idx_oper_one])->key);
				break;
			}
			if (str[token_end+1] != 0 && is_in_t_arr_dic_str(shell->oper, &str[token_end+1]) != -1)
			{	
				oper_ad = 1;
				break;
			}
		}
		token_end++;
		(void)c;
	}
	/*  A implementer le quote> et la terminaison
	➜  ~ echo 'so"
		quote> sdf"
		quote> 
		➜  ~ echo 'so"
		sdf"  
		quote> '
		so"
		sdf"
	*/
	//if (in_double_quote || in_single_quote)
	//	;
	
	token_end+=oper_ad;
	*start = token_end;
	// Allocate and copy the token
	token_len = token_end - token_start;

	token = malloc(token_len + 1);
	if (!token)
		return (NULL);
	strncpy(token, str + token_start, token_len);
	token[token_len] = '\0';
	return (token);
}


/*
have to fix command
cat<system.log>rep.txt
*/


// Main split function
/*
	EDGE CASES
	a\"b\"c\'d\'e				
	\"Mamman\'echo\'Papa\" 		
	\"%USER\"and\’$USER\’		
*/
t_arr 	*custom_split(const char *str, t_shell * shell)
{
	int		pos;
	int		token_index;
	t_arr	*result;

	
	if (!str)
		return NULL;
	result = malloc(sizeof(t_arr));
	if (!result)
		perror("Malloc");
	result->len = count_arg(str, shell); //have to implemente the <quote> if " or ' not closed
        result->arr = malloc(sizeof(char *) * (result->len + 1));
        if (!result->arr)
        {
                free(result);
                perror("Malloc");
        }
        pos = 0;
        token_index = 0;
        while (token_index < result->len)
        {
                result->arr[token_index] = extract_arg(str, &pos, shell);
                if (!result->arr[token_index])
                {
                        for (int i = 0; i < token_index; i++)
                                free(result->arr[i]);
                        free(result->arr);
                        free(result);
                        perror("Erreur d'allocation pour les tokens");
                }
                token_index++;
        }
        result->arr[token_index] = NULL;
        return result;
}