/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piping.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvagapov <vvagapov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 20:06:21 by vvagapov          #+#    #+#             */
/*   Updated: 2023/09/09 22:06:11 by vvagapov         ###   ########.fr       */
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
	return (SUCCESS);
	// Add check if directory etc
}

int	execute_cmd(t_shell *core, t_command *command)
{
	char	*paths;
	char	**paths_split;

	paths = fetch_env("PATH", core);
	if (!paths)
	{
		// what to do in this case? anything extra?
		return (1);
	}
	paths_split = split_path(paths);
	if (!paths_split)
	{
		core->cur_process.error_index = MALLOC_ERROR;
		// TODO: set error
		return (1);
	}
	if (execute(core, paths_split, command) != SUCCESS)
	{
		// TODO: set error
		return (1);
	}
	return (SUCCESS);
	/* char	*args[2] = {"", NULL};

	ft_putendl_fd(command->cmd_name, 2);

	execve(ft_strjoin("/bin/", command->cmd_name), args, core->env);
	return (0); */
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
		// What's the difference between malloc error and malloc fail?
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
