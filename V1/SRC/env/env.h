/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiefer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 22:30:32 by nkiefer           #+#    #+#             */
/*   Updated: 2025/08/13 22:30:34 by nkiefer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

# include "minishell.h"

t_list	*init_env(char **envp);
char	**list_to_envp(t_list *env);
void	free_env_list(t_list *lst);
int		env_len(t_list *env);
void	print_env(t_list *env);

#endif // ENV_H
