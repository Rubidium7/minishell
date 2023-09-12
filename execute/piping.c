/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piping.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvagapov <vvagapov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 20:06:21 by vvagapov          #+#    #+#             */
/*   Updated: 2023/09/12 15:37:26 by vvagapov         ###   ########.fr       */
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

	//printf("%s args:\n", command->cmd_name); //debug
	//print_ar(command->cmd_ar); //debug
	//printf("%s args end\n", command->cmd_name); //debug
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
	if (ft_strcmp(command->cmd_name, "cd")
		&& ft_strcmp(command->cmd_name, "echo")
		&& ft_strcmp(command->cmd_name, "env")
		&& ft_strcmp(command->cmd_name, "exit")
		&& ft_strcmp(command->cmd_name, "export")
		&& ft_strcmp(command->cmd_name, "pwd")
		&& ft_strcmp(command->cmd_name, "unset"))
		return (FALSE);
	return (TRUE);
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
		core->cur_process.error_index = MALLOC_FAIL;
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
}

int	handle_child(t_command *curr_command, int **pipes, t_shell *core)
{
/*	printf("child name: %s\n", curr_command->cmd_name);  //debug
 	printf("red_in: %d\n", curr_command->red_in);
	printf("red_out: %d\n", curr_command->red_out); */
	if (dup_input(curr_command, pipes) == -1
	|| dup_output(curr_command, pipes) == -1)
	{
		// the below is useless, right?
		// core->cur_process.error_index = DUP_ERROR;
		ft_putstr_fd("dup error\n", 2); //debug
		exit(1);
	}
	close_pipes(pipes);
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

// Joins the path to command name and returns the result if successful
char	*join_path(t_shell *core, char* path, char *cmd_name)
{
	char	*full_path;
	char	*path_with_slash;

	path_with_slash = ft_strjoin(path, "/");
	if (!path_with_slash)
	{
		core->cur_process.error_index = MALLOC_FAIL;
		return (NULL);
	}
	full_path = ft_strjoin(path_with_slash, cmd_name);
	free(path_with_slash);
	if (!full_path)
	{
		core->cur_process.error_index = MALLOC_FAIL;
		return (NULL);
	}
	return (full_path);
}

char	*find_cmd_path(t_shell *core, t_command *command)
{
	int		i;
	char	*cmd_path;
	char	**paths;
	char	**paths_split;

	if (is_builtin(command))
	{
		//run_builtin(command);
		// TODO: handle return value of run_builtin?
	}
	//printf("executing %s[%d]\n", command->cmd_name, command->index);
	paths = fetch_env("PATH", core);
	if (!paths)
	{
		// what to do in this case? anything extra?
		//printf("no path found\n"); //debug
		core->cur_process.error_index = MALLOC_FAIL;
		return (1);
	}
	paths_split = split_path(paths);
	if (!paths_split)
	{
		//printf("path split error\n"); //debug
		core->cur_process.error_index = MALLOC_FAIL;
		return (1);
	}
	i = 0;
	while (paths_split[i])
	{
		cmd_path = join_path(core, paths_split[i], command->cmd_name);
		if (!cmd_path)
			return (NULL);
		if (access(cmd_path, X_OK) == SUCCESS)
			return (cmd_path);
		free(cmd_path);
		i++;
	}
	return (NULL);
}

int	has_args(char **args)
{
	int	i;

	i = 0;
	while (args[i])
		i++;
	if (i > 1)
		return (TRUE);
	return (FALSE);
}

int	no_child_needed(t_command *commands)
{
	if (list_len(commands) > 1)
		return (FALSE);
	if (!ft_strcmp(commands->cmd_name, "export") && has_args(commands->cmd_ar))
			return (TRUE);
	if (!ft_strcmp(commands->cmd_name, "cd")
		|| !ft_strcmp(commands->cmd_name, "exit")
		|| !ft_strcmp(commands->cmd_name, "unset"))
		return (TRUE);
	return (FALSE);
}

int	execute_with_children(t_shell *core, t_command *commands)
{
	int			**pipes;
	t_command	*curr_command;
	pid_t		*children;
	int			len;
	int			ret;
	char		*cmd_path;
	
	len = list_len(commands);
	pipes = malloc_pipes(len - 1);
	if (!pipes)
	{
		core->cur_process.error_index = MALLOC_FAIL;
		return (1);
	}
	if (open_pipes(pipes) != SUCCESS)
	{
		core->cur_process.error_index = PIPE_FAIL;
		return (1);
	}
	// prepare an array of pids for child processes
	children = malloc(sizeof(pid_t) * len);
	curr_command = commands;
	// TODO: handle first and last case
	while (curr_command)
	{
		// create a child process
		// TODO: put path search here
		cmd_path = find_cmd_path(core, curr_command);
		//if (access(curr_command->cmd_ar, X_OK))
		children[curr_command->index] = fork();
		if (!children[curr_command->index])
			handle_child(curr_command, pipes, core);
		curr_command = curr_command->next;
	}
	close_pipes(pipes);
	ret = wait_for_children(children, len);
	free_pipes(pipes);
	return (ret);
}

int	pipeline_execution(t_shell *core, t_command *commands)
{
	int	ret;

	// TODO: shorten?
	if (no_child_needed(commands))
	{
		// more stuff needed?
		ret = execute_cmd(core, commands);
	}
	else
	{
		ret = execute_with_children(core, commands);
	}
	return (ret);
}
