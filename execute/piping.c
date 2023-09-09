/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piping.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvagapov <vvagapov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 20:06:21 by vvagapov          #+#    #+#             */
/*   Updated: 2023/09/09 18:53:54 by vvagapov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include "../includes/structs.h"
#include "../includes/minishell.h"

char	**split_path(char* path)
{
	return ft_split(path, ':');
}

int	execute(t_shell *shell, char** paths, t_command *command)
{
	int		i;
	char	*exe_path;

	i = 0;
	if (command->cmd_name[0] == '/' && access(exe_path, X_OK))
		execve(command->cmd_name, command->cmd_ar, shell->env);
	while (paths[i])
	{
		exe_path = ft_strjoin(paths[i], command->cmd_name);
		if (access(exe_path, X_OK))
		{
			execve(exe_path, command->cmd_ar, shell->env);
		}
	}
	execve(exe_path, command->cmd_ar, shell->env);
	return (0);
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
		printf("opened %d %d\n", pipes[i][0], pipes[i][1]);
		i++;
	}
	return (0);
}

void close_pipes(int **pipes)
{
	if (!pipes)
		printf("pipes is NULL\n");
	printf("almost closing soon...\n");
	while (*pipes)
	{
		printf("closing soon...\n");
		printf("closing %d %d\n", (*pipes)[0], (*pipes)[1]);
		close((*pipes)[0]);
		close((*pipes)[1]);
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

	ft_putendl_fd(command->cmd_name, 2);

	execve(ft_strjoin("/bin/", command->cmd_name), args, shell->env);
	return (0);
}

/* int	execute_node(t_command *head, t_shell *core)
{

} */

int	pipeline_execution(t_shell *core, t_command *head)
{
	int			**pipes;
	t_command	*curr_node;
	int			in_fd;
	int			out_fd;
	pid_t		*children;
	int			i;
	int			len;

	len = list_len(head);
	printf("helo\n");
	// prepare enough pipes to connect all child processes
	pipes = malloc_pipes(len - 1);
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
	// prepare an array of pids for child processes
	// make this NULL-terminated too maybe?
	children = malloc(sizeof(pid_t) * len);
	curr_node = head;
	// TODO: handle first and last case
	while (curr_node)
	{
		// fcreate a child process
		children[curr_node->index] = fork();
		if (!children[curr_node->index])
		{
			printf("cmd_name: %s\n", curr_node->cmd_name);
			printf("red_in: %d\n", curr_node->red_in);
			printf("red_out: %d\n", curr_node->red_out);
			// for a child process:
			// set red_in
			if (curr_node->red_in != DEFAULT)
				in_fd = curr_node->red_in;
			else
			{
				// if no red_in was given 
				// and it's not the first node
				if (curr_node->index)
					// input from pipe
					in_fd = pipes[curr_node->index - 1][0];
				else
					// input from stdin
					in_fd = STDIN_FILENO;
			}
			printf("in_fd: %d\n", in_fd);
			dup2(in_fd, STDIN_FILENO);
			// set red_out
			if (curr_node->red_out != DEFAULT)
				out_fd = curr_node->red_out;
			else
			{
				// if no red_out was given 
				// and it's not the last node
				if (curr_node->next)
					// output to the READ end of the pipe of the next command
					out_fd = pipes[curr_node->index][1];
				else
					// if it's the last node, output to stdout
					out_fd = STDOUT_FILENO;
			}
			printf("out_fd: %d\n", out_fd);
			//if (pipes[pipe_index])
				dup2(out_fd, STDOUT_FILENO);
			if (pipes[curr_node->index])
			{
				close(pipes[curr_node->index][1]);
				close(pipes[curr_node->index][0]);
			}
			if (pipes[curr_node->index - 1])
			{
				close(pipes[curr_node->index - 1][1]);
				close(pipes[curr_node->index - 1][0]);
			}
			execute_cmd(core, curr_node);
		}
		curr_node = curr_node->next;
	}
	close_pipes(pipes);
	free_pipes(pipes);
	i = 0;
	while (i < len)
	{
		printf("waiting for %d\n", children[i]);
		waitpid(children[i], NULL, 0);
		i++;
	}
	//
	return (0);
}
