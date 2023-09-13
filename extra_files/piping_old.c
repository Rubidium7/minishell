/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piping.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvagapov <vvagapov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 20:06:21 by vvagapov          #+#    #+#             */
/*   Updated: 2023/09/03 21:01:19 by vvagapov         ###   ########.fr       */
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
		/* if (red_in)
			in_fd = red_in;
		else */
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

	res = malloc(sizeof(int*) * num + 1);
	if (!res)
		return (NULL);
	res[num] = NULL;
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

void	free_pipes(int **pipes)
{
	int i;
	
	i = 0;
	while (pipes[i])
	{
		free(pipes[i]);
		i++;
	}
	free(pipes);
}

int	open_pipes(int **pipes)
{
	int	i;

	i = 0;
	while (pipes[i])
	{
		if (pipe(pipes[i]) == -1)
		{
			return (1);
		}
		i++;
	}
	return (0);
}

void close_pipes(int **pipes)
{
	while (*pipes)
	{
		close(*pipes[0]);
		close(*pipes[1]);
		pipes++;
	}
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

int	execute_cmd(t_shell *shell, t_command *command)
{
	char	*args[2] = {"", NULL};

	execve(ft_strjoin("/usr/bin/", command->cmd_name), args, shell->env_list);
}

/* int	execute_node(t_command *head, t_shell *core)
{

} */

int	pipeline_execution(t_shell *core, t_command *head)
{
	int			**pipes;
	t_command	*curr_node;
	int			pipe_index;
	int			in_fd;
	int			out_fd;

	pipes = malloc_pipes(list_len(head) - 1);
	if (!pipes)
	{
		core->cur_process.error_index = MALLOC_ERROR;
		return (1);
	}
	if (open_pipes(pipes))
	{
		core->cur_process.error_index = PIPE_ERROR;
		return (1);
	}
	curr_node = head;
	// handle first and last case
	pipe_index = 0;
	while (curr_node)
	{
		if (curr_node->red_in != DEFAULT)
			in_fd = curr_node->red_in;
		else
			in_fd = pipes[pipe_index][0];
		dup2(in_fd, STDIN_FILENO);
		if (curr_node->red_out != DEFAULT)
			out_fd = curr_node->red_out;
		else
		{
			if (pipes[pipe_index + 1])
				out_fd = pipes[pipe_index + 1][1];
			else
				out_fd = STDOUT_FILENO;
		}
		if (pipes[pipe_index])
			dup2(out_fd, STDIN_FILENO);
		close(pipes[pipe_index][1]);
		close(pipes[pipe_index][0]);
		curr_node = curr_node->next;
		pipe_index++;
	}
	close_pipes(pipes);
	free_pipes(pipes);
	//waitpid(pid1, NULL, 0);
	return (0);
}
