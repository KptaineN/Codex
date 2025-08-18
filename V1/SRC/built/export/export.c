/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiefer <nkiefer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 15:55:22 by nkiefer           #+#    #+#             */
/*   Updated: 2025/08/13 15:58:20 by nkiefer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "export.h"

void	print_env_debug(t_list *env)
{
	t_env	*e;

	while (env)
	{
		e = env->content;
		printf("[DEBUG] %s=", e->key);
		if (e->value)
			printf("%s\n", e->value);
		else
			printf("\n");
		env = env->next;
	}
}

int	builtin_export(t_shell *shell, char **argv)
{
	int	error;
	int	i;

	i = 0;
	if (!argv[1])
		return (export_no_arguments(shell));
	error = 0;
	i = 1;
	while (argv[i])
	{
		error |= process_export_argument(argv[i], shell);
		i++;
	}
	shell->exit_status = error;
	return (error);
}
