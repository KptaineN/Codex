/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiefer <nkiefer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 16:24:16 by eganassi          #+#    #+#             */
/*   Updated: 2025/08/16 13:00:04 by nkiefer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	is_line_empty(const char *s)
{
	return (!s || *s == '\0');
}

static int	must_exit(const char *s)
{
	return (ft_strcmp(s, "exit") == 0);
}

static void	ensure_fallback_cmd(t_shell *sh)
{
	t_list	*node;

	if (sh->n_tokens > 0 && sh->n_cmd == 0)
	{
		sh->n_cmd = 1;
		node = ft_lstnew(&sh->tokens[0]);
		if (!node)
		{
			perror("ft_lstnew");
			exit(1);
		}
		sh->cmd_head = node;
		sh->cmd_tail = node;
	}
}

static int	parse_and_prepare(t_shell *sh, char *line)
{
	sh->input = line;
	sh->parsed_args = custom_split(line, sh);
	if (!sh->parsed_args)
		return (-1);
	attribute_token_type(sh);
	assign_redirs(sh);
	build_cmd_list(sh);
	ensure_fallback_cmd(sh);
	sh->pids = malloc(sizeof(pid_t) * sh->n_cmd);
	if (!sh->pids)
		perror("malloc pids");
	return (0);
}

int	process_input(t_shell *sh, char *in)
{
	char	*line;

	if (is_line_empty(in))
		return (free(in), 0);
	add_history(in);
	if (must_exit(in))
		return (free(in), 1);
	line = expand_input(in, sh);
	if (!line)
		return (free(in), 0);
	if (parse_and_prepare(sh, line) < 0)
	{
		free(line);
		free(in);
		return (0);
	}
	launch_process(sh);
	cleanup_shell_iter(sh);
	free(line);
	free(in);
	return (2);
}
