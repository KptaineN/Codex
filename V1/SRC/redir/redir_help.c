/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_help.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiefer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 02:24:41 by nkiefer           #+#    #+#             */
/*   Updated: 2025/08/18 02:24:43 by nkiefer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redir.h"

/* ouvre après expansion ; -2 si ambiguous, -1 si open fail, fd sinon */
int	open_from_expansion(char *raw, t_shell *sh, int flags, int mode)
{
	char	*file;
	int		fd;

	file = expand_filename_if_needed(raw, sh);
	if (is_ambiguous(file))
	{
		ambiguous(raw);
		free(file);
		return (-2);
	}
	fd = open(file, flags, mode);
	free(file);
	if (fd < 0)
		return (-1);
	return (fd);
}

/* gère le heredoc exactement comme avant (avec exit(130) si -2) */
int	handle_heredoc_child(char *raw, t_shell *sh)
{
	t_delim	d;
	int		hfd;

	d = parse_delim(raw);
	hfd = build_heredoc_fd(d, sh);
	free(d.clean);
	if (hfd == -2)
		exit(130);
	if (hfd < 0)
		return (1);
	dup2(hfd, STDIN_FILENO);
	close(hfd);
	return (0);
}

int	open_and_dup_in(char *raw, t_shell *sh)
{
	int	fd;

	fd = open_from_expansion(raw, sh, O_RDONLY, 0);
	if (fd == -2)
		return (1);
	if (fd < 0)
	{
		perror(raw);
		return (1);
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
	return (0);
}

int	open_and_dup_out_trunc(char *raw, t_shell *sh)
{
	int	fd;

	fd = open_from_expansion(raw, sh, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == -2)
		return (1);
	if (fd < 0)
	{
		perror(raw);
		return (1);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (0);
}

int	open_and_dup_out_append(char *raw, t_shell *sh)
{
	int	fd;

	fd = open_from_expansion(raw, sh, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (fd == -2)
		return (1);
	if (fd < 0)
	{
		perror(raw);
		return (1);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (0);
}
