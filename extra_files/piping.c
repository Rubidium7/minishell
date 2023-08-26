/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piping.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvagapov <vvagapov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 20:06:21 by vvagapov          #+#    #+#             */
/*   Updated: 2023/08/26 21:59:40 by vvagapov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include "../includes/structs.h"
#include "../includes/minishell.h"

int main(int ac, char **av, char **ev)
{
	int 	fds[2];
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

char	**split_path(char* path)
{
	return ft_split(path, ':');
}

int	execute(t_shell *shell, char** paths, t_command *command)
{
	int		i;
	char	*exe_path;

	i = 0;
	if (command->cmd_name[0] == '/' && access(exe_path, F_OK))
		execve(command->cmd_name, command->cmd_ar, shell->env);
	while (paths[i])
	{
		exe_path = ft_strjoin(paths[i], command->cmd_name);
		if (access(exe_path, F_OK))
		{
			execve(exe_path, command->cmd_ar, shell->env);
		}
	}
	execve(exe_path, command->cmd_ar, shell->env);
	// Add check if directory etc
}

int	**malloc_pipes(int num)
{
	int	**res;
	int	i;

	res = malloc(sizeof(int*) * num);
	if (!res)
		return (NULL);
	i = 0;
	while (i < num)
	{
		res[i] = malloc(sizeof(int) * 2);
		if (!res[i])
		{
			free(res);
			return (NULL);
		}
		i++;
	}
	return (res);
}

int	list_len(t_command *list)
{
	int res;

	res = 0;
	while(list)
	{
		list = list->next;
		res++;
	}
	return (res);
}

int mypipe(t_shell *shell, t_command *commands)
{
	int			**pipes;
	t_command	*temp;

	pipes = malloc_pipes(list_len(commands));
	if (!pipes)
		return (1);
	temp = commands;
	// handle first and last case
	while (temp)
	{
		while ()
		temp = temp->next;
	}
	return (0);
}
