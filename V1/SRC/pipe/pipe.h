/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiefer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 23:34:17 by nkiefer           #+#    #+#             */
/*   Updated: 2025/08/13 23:34:19 by nkiefer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPE_H
# define PIPE_H

# include "minishell.h"

int		open_pipe_if_needed(int has_next, int pipe_fd[2]);
void	close_if_valid(int fd);
void	wait_pipeline(t_shell *sh, int count);

#endif // PIPE_H
