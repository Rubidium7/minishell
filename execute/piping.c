/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piping.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvagapov <vvagapov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 20:06:21 by vvagapov          #+#    #+#             */
/*   Updated: 2023/09/11 23:42:05 by vvagapov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include "structs.h"
#include "minishell.h"

char	**split_path(char* path)
{
	return ft_split(path, ':');
}


int	execute(t_shell *shell, char** paths, t_command *command)
{
	int		i;
	char	*exe_path;

	printf("%s args:\n", command->cmd_name); //debug
	print_ar(command->cmd_ar); //debug
	printf("%s args end\n", command->cmd_name); //debug
	if (command->cmd_name[0] == '/' && access(command->cmd_name, X_OK))
	{
		//printf("no path used\n"); //debug
		execve(command->cmd_name, command->cmd_ar, shell->env);
	}
	i = 0;
	while (paths[i])
	{
		exe_path = ft_strjoin(ft_strjoin(paths[i], "/"), command->cmd_name);
		if (!access(exe_path, X_OK))
		{
			//printf("path accessed!\n"); //debug
			execve(exe_path, command->cmd_ar, shell->env);
		}
		i++;
	}
	exit (1);
	// Add check if directory etc
}

int	run_builtin(t_command *command)
{
	(void)command;
	// TODO: implement
	return (0);
}

int	is_builtin(t_command *command)
{
	(void)command;
	// TODO: implement
	return (0);
}

int	execute_cmd(t_shell *core, t_command *command)
{
	char	*paths;
	char	**paths_split;

	if (is_builtin(command))
	{
		run_builtin(command);
		// TODO: handle return value of run_builtin?
		exit(1);
	}
	printf("executing %s[%d]\n", command->cmd_name, command->index);
	paths = fetch_env("PATH", core);
	if (!paths)
	{
		// what to do in this case? anything extra?
		//printf("no path found\n"); //debug
		return (1);
	}
	paths_split = split_path(paths);
	if (!paths_split)
	{
		//printf("path split error\n"); //debug
		core->cur_process.error_index = MALLOC_ERROR;
		// TODO: set error
		return (1);
	}
	if (execute(core, paths_split, command) != SUCCESS)
	{
		// TODO: set error
		//printf("execute error\n"); //debug
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
	printf("child name: %s\n", curr_command->cmd_name);  //debug
/* 	printf("red_in: %d\n", curr_command->red_in);
	printf("red_out: %d\n", curr_command->red_out); */
	if (dup_input(curr_command, pipes) == -1
	|| dup_output(curr_command, pipes) == -1)
	{
		// the below is useless, right?
		// core->cur_process.error_index = DUP_ERROR;
		printf("dup error\n"); //debug
		exit(1);
	}
	if (!is_last_command(curr_command) && pipes[curr_command->index])
	{
		printf("(match) closing fd %d in child %s[%d]\n", pipes[curr_command->index][1], curr_command->cmd_name, curr_command->index);  //debug
		close(pipes[curr_command->index][1]);
		printf("(match) closing fd %d in child %s[%d]\n", pipes[curr_command->index][0], curr_command->cmd_name, curr_command->index); //debug
		close(pipes[curr_command->index][0]);
	}
	if (!is_first_command(curr_command))
	{
		printf("(prev) closing fd %d in child %s[%d]\n", pipes[curr_command->index - 1][1], curr_command->cmd_name, curr_command->index); //debug
		close(pipes[curr_command->index - 1][1]);
		printf("(prev) closing fd %d in child %s[%d]\n", pipes[curr_command->index - 1][0], curr_command->cmd_name, curr_command->index); //debug
		close(pipes[curr_command->index - 1][0]);
	}
	execute_cmd(core, curr_command);
	//execute_placeholder(core, curr_command);
	exit(1);
}

int	wait_for_children(pid_t *children, int len)
{
	int	i;
	int	ret;

	i = 0;
	ret = 0;
	while (i < len)
	{
		waitpid(children[i], &ret, 0);
		i++;
	}
	// wouldn't this contain only last return value?
	return(WEXITSTATUS(ret));
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
			handle_child(curr_command, pipes, core);
		}
		curr_command = curr_command->next;
	}
	close_pipes(pipes);
	free_pipes(pipes);
	wait_for_children(children, len);
	return (0);
}
