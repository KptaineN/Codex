/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pid.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiefer <nkiefer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 16:28:09 by nkiefer           #+#    #+#             */
/*   Updated: 2025/08/16 16:33:40 by nkiefer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "launcher.h"

ssize_t	read_pid_exact(int fd, pid_t *out)
{
	ssize_t	readn;
	size_t	total;
	char	*p;

	if (!out)
		return (-1);
	total = 0;
	p = (char *)out;
	while (total < sizeof(pid_t))
	{
		readn = read(fd, p + total, sizeof(pid_t) - total);
		if (readn < 0)
		{
			perror("add_pid_env: read");
			return (-1);
		}
		if (readn == 0)
			break ;
		total += (size_t)readn;
	}
	return ((ssize_t)total);
}

void	add_pid_env(t_shell *shell, int fd)
{
	pid_t	pid;
	ssize_t	n;
	char	*msg;

	n = read_pid_exact(fd, &pid);
	if (n < 0)
		return ;
	if ((size_t)n < sizeof(pid_t))
	{
		msg = "add_pid_env: pipe ferme prematurement\n";
		write(2, msg, ft_strlen(msg));
		return ;
	}
	set_env_pid(shell, pid);
}

void	set_env_pid(t_shell *shell, pid_t pid)
{
	char	buf[32];

	ft_itoa_inplace(buf, (int)pid);
	set_env_value(&shell->env, "PID", buf);
}

void	send_pid(int fd, int pid)
{
	write(fd, "PID=", sizeof("PID="));
	write(fd, &pid, sizeof(pid));
}

void	update_last_pid_env(t_shell *sh)
{
	char	buf[32];
	int		last;

	last = (int)sh->pids[sh->n_cmd - 1];
	ft_itoa_inplace(buf, last);
	set_env_value(&sh->env, "PID", buf);
}
