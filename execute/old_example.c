/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   old_example.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvagapov <vvagapov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 20:06:21 by vvagapov          #+#    #+#             */
/*   Updated: 2023/09/09 17:26:00 by vvagapov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include "../includes/structs.h"
#include "../includes/minishell.h"

int old_main(int ac, char **av, char **ev)
{
	int		fds[2];
	pid_t	child;
	pid_t	child2;
	char	*args[2] = {"", NULL};
	int		in_fd;

	pipe(fds);
	child = fork();
	if (!child)
	{
		dup2(fds[1], 1);
		close(fds[0]);
		execve("/bin/ls", args, ev);
		write(2, "ls hi\n", 6);
	}
	child2 = fork();
	if (!child2)
	{
		if (red_in)
			in_fd = red_in;
		else
			in_fd = fds[0];
		dup2(in_fd, 0);
		close(fds[1]);
		execve("/usr/bin/grep", av, ev);
		write(2, "grep yo\n", 8);
	}
	return (0);
}
