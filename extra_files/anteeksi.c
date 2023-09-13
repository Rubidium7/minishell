/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   anteeksi.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvagapov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 19:34:21 by vvagapov          #+#    #+#             */
/*   Updated: 2023/08/20 20:06:08 by vvagapov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>

//stdin 0
//stdout 1

int main(int ac, char **av, char **ev)
{
	int fd = open("mutsis", O_RDWR);
	dup2(fd, 0);
	execve("/usr/bin/grep", av, ev);
	write(2, "error\n", 6);
	return (0);
}
