/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiefer <nkiefer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 22:20:10 by eganassi          #+#    #+#             */
/*   Updated: 2025/07/14 15:41:06 by nkiefer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */




// display subtoken
/*void print_all_parts(t_shell *shell)
{
	int n = 0;
	int n_parts;
	t_subtoken *parts;
	t_token *token;
	while(1)
	{
		token = &shell->tokens[n++];
		if (token->type != TOKEN_WORD)
		{	
			if (n == shell->n_tokens)
				return;
			printf("%s\n", token->value);
			continue;
		}
		n_parts = token->u.all_parts.n_parts;
		parts = token->u.all_parts.parts;
		int idx_parts = 0;
		t_subtoken *subtoken;
		char *types[] ={"no quote", "single quote", "double quote"};
		while(idx_parts<n_parts)
		{
			subtoken = &parts[idx_parts];
			printf("val {%.*s} \t type {%s}", subtoken->len,subtoken->p, types[subtoken->type]);
			idx_parts++;
		}
		if (n == shell->n_tokens)
			return;
		printf("\n");
	}
	printf("\n");
}*/

/* Print dictionary-like array in the form key=value
void print_dic(t_arr *dic)
{
	int		i;
	char	**pair;

	i = 0;
	while (i < dic->len)
	{
		pair = (char **)dic->arr[i];
		printf("%s\t%p\n", pair[0], (void *)pair[1]);
		i++;
	}
}*/

