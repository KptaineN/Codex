/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiefer <nkiefer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 22:41:19 by eganassi          #+#    #+#             */
/*   Updated: 2025/08/07 15:27:58 by nkiefer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

bool is_command(char *str, t_list *env)
{
    char *cmd_path;

    cmd_path = find_command_path(str, env);
    if (cmd_path)
    {
        free(cmd_path);
        return (1);
    }
    return (0);
}
