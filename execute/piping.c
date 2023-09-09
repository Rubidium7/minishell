/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piping.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvagapov <vvagapov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 20:06:21 by vvagapov          #+#    #+#             */
/*   Updated: 2023/09/09 21:29:39 by vvagapov         ###   ########.fr       */
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

int	dup_input(t_command *curr_command, int **pipes)
{
	int			in_fd;
	
	if (curr_command->red_in != DEFAULT)
		in_fd = curr_command->red_in;
	else
	{
		// if no red_in was given 
		// and it's not the first node
		if (curr_command->index)
			// input from the pipe
			in_fd = pipes[curr_command->index - 1][0];
		else
			// input from stdin
			in_fd = STDIN_FILENO;
	}
	printf("in_fd: %d\n", in_fd);
	return (dup2(in_fd, STDIN_FILENO));
}

int dup_output(t_command *curr_command, int **pipes)
{
	int			out_fd;

	// set red_out
	if (curr_command->red_out != DEFAULT)
		out_fd = curr_command->red_out;
	else
	{
		// if no red_out was given 
		// and it's not the last node
		if (curr_command->next)
			// output to the pipe
			out_fd = pipes[curr_command->index][1];
		else
			// if it's the last node, output to stdout
			out_fd = STDOUT_FILENO;
	}
	printf("out_fd: %d\n", out_fd);
	//if (pipes[pipe_index])
	return (dup2(out_fd, STDOUT_FILENO));
}

int	handle_child(t_command *curr_command, int **pipes, t_shell *core)
{
	printf("cmd_name: %s\n", curr_command->cmd_name);
	printf("red_in: %d\n", curr_command->red_in);
	printf("red_out: %d\n", curr_command->red_out);
	if (dup_input(curr_command, pipes) == -1
	|| dup_output(curr_command, pipes) == -1)
	{
		core->cur_process.error_index = DUP_ERROR;
		return (1);
	}
	if (pipes[curr_command->index])
	{
		close(pipes[curr_command->index][1]);
		close(pipes[curr_command->index][0]);
	}
	if (pipes[curr_command->index - 1])
	{
		close(pipes[curr_command->index - 1][1]);
		close(pipes[curr_command->index - 1][0]);
	}
	execute_cmd(core, curr_command);
	return (SUCCESS);
}

void	wait_for_children(pid_t *children, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		waitpid(children[i], NULL, 0);
		i++;
	}
}

int	pipeline_execution(t_shell *core, t_command *commands)
{
	int			**pipes;
	t_command	*curr_command;
	pid_t		*children;
	int			len;

	len = list_len(commands);
	// prepare enough pipes to connect all child processes
	pipes = malloc_pipes(len - 1);
	if (!pipes)
	{
		core->cur_process.error_index = MALLOC_ERROR;
		return (1);
	}
	if (open_pipes(pipes) != SUCCESS)
	{
		core->cur_process.error_index = PIPE_ERROR;
		return (1);
	}
	// prepare an array of pids for child processes
	// make this NULL-terminated too maybe?
	children = malloc(sizeof(pid_t) * len);
	curr_command = commands;
	// TODO: handle first and last case
	while (curr_command)
	{
		// fcreate a child process
		children[curr_command->index] = fork();
		if (!children[curr_command->index])
		{
			if (handle_child(curr_command, pipes, core) != SUCCESS)
			{
				// TODO: clean memory everywhere
				// TODO: actually test error
				close_pipes(pipes);
				free_pipes(pipes);
				return (1);
			}
		}
		curr_command = curr_command->next;
	}
	close_pipes(pipes);
	free_pipes(pipes);
	wait_for_children(children, len);
	return (0);
}
