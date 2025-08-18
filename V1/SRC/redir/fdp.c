/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiefer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 02:25:26 by nkiefer           #+#    #+#             */
/*   Updated: 2025/08/18 02:25:30 by nkiefer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redir.h"

/* Copie raw sans guillemets dans d->clean et met d->quoted = 1 si trouvé.
   Retourne 1 si OK, 0 si malloc fail. */
static int	copy_no_quotes(t_delim *d, const char *raw)
{
	size_t	i;
	size_t	j;
	char	*clean;

	clean = malloc(ft_strlen(raw) + 1);
	if (!clean)
		return (0);
	i = 0;
	j = 0;
	while (raw[i])
	{
		if (raw[i] == '\'' || raw[i] == '\"')
		{
			d->quoted = 1;
			i++;
		}
		else
			clean[j++] = raw[i++];
	}
	clean[j] = '\0';
	d->clean = clean;
	return (1);
}

t_delim	parse_delim(const char *raw)
{
	t_delim	d;

	d.raw = (char *)raw;
	d.clean = NULL;
	d.quoted = 0;
	if (!raw)
		return (d);
	if (!copy_no_quotes(&d, raw))
		return (d);
	return (d);
}

static int	apply_one_redir(t_redir *r, t_shell *sh)
{
	if (r->type == R_IN)
		return (open_and_dup_in(r->arg, sh));
	if (r->type == R_OUT_TRUNC)
		return (open_and_dup_out_trunc(r->arg, sh));
	if (r->type == R_OUT_APPEND)
		return (open_and_dup_out_append(r->arg, sh));
	return (handle_heredoc_child(r->arg, sh));
}

int	apply_redirs_in_child(t_cmd *c, t_shell *sh)
{
	int	i;
	int	ret;

	i = 0;
	while (i < c->r_count)
	{
		ret = apply_one_redir(&c->r[i], sh);
		if (ret != 0)
			return (1);
		i++;
	}
	return (0);
}
