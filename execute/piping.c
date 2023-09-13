/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piping.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvagapov <vvagapov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 20:06:21 by vvagapov          #+#    #+#             */
/*   Updated: 2023/09/13 19:19:27 by vvagapov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**split_path(char* path)
{
	return ft_split(path, ':');
	//https://i.kym-cdn.com/photos/images/newsfeed/001/889/888/265.jpeg
}

int	run_builtin(t_shell *core, t_command *command)
{
	(void)command;
	if (!ft_strcmp(command->cmd_name, "pwd"))
		return (pwd(core));
	else if (!ft_strcmp(command->cmd_name, "exit"))
		return (ft_exit(core, command));
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

void	execute_cmd(t_shell *core, t_command *command, char *exe_path)
{
	if (is_builtin(command))
		exit(run_builtin(core, command));
	else
		execve(exe_path, command->cmd_ar, core->env);
}

void	handle_child(t_command *curr_command, int **pipes, t_shell *core,
	char *exe_path)
{
/*	printf("child name: %s\n", curr_command->cmd_name);  //debug
 	printf("red_in: %d\n", curr_command->red_in);
	printf("red_out: %d\n", curr_command->red_out); */
	set_child_signals();
	if (dup_input(curr_command, pipes) == -1
	|| dup_output(curr_command, pipes) == -1)
	{
		// the below is useless, right?
		// core->cur_process.error_index = DUP_ERROR;
		error_print(EXEC_ERROR);
		exit(1);
	}
	close_pipes(pipes);
	//free_pipes(pipes); // maybe needed? nah
	execute_cmd(core, curr_command, exe_path);
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
	return(ret);
}

// Joins the path to command name and returns the result if successful,
// Otherwise sets the error index and returns NULL
char	*join_path(t_shell *core, char* path, char *cmd_name)
{
	char	*full_path;
	char	*path_with_slash;

	path_with_slash = ft_strjoin(path, "/"); // malloc
	if (!path_with_slash)
	{
		core->cur_process.error_index = MALLOC_FAIL;
		return (NULL);
	}
	full_path = ft_strjoin(path_with_slash, cmd_name); // malloc
	free(path_with_slash);
	if (!full_path)
	{
		core->cur_process.error_index = MALLOC_FAIL;
		return (NULL);
	}
	return (full_path);
}

/* char *check_path(t_shell *core, char *path, t_command *command)
{
	char	*exe_path;

	exe_path = join_path(core, path, command->cmd_name);

} */
char	**fetch_paths_array(t_shell *core)
{
	char	*paths;
	char	**paths_split;

	paths = fetch_env("PATH", core); // malloc
	if (!paths)
	{
		// what to do in this case? anything extra?
		core->cur_process.error_index = MALLOC_FAIL;
		return (NULL);
	}
	paths_split = split_path(paths); // malloc
	if (!paths_split)
	{
		core->cur_process.error_index = MALLOC_FAIL;
	}
	free(paths);
	return (paths_split);
}

// Go through Paths and find the correct one.
// If not found return NULL
char	*find_exe_path(t_shell *core, t_command *command)
{
	int		i;
	char	*exe_path;
	char	**paths_split;

	paths_split = fetch_paths_array(core); // malloc
	if (!paths_split)
		return (NULL);
	i = 0;
	while (paths_split[i])
	{
		exe_path = join_path(core, paths_split[i], command->cmd_name); // malloc
		if (!exe_path || access(exe_path, X_OK) == SUCCESS)
		{
			free_ar(paths_split);
			return (exe_path);
		}
		free(exe_path);
		i++;
	}
	free_ar(paths_split);
	// how to differenciate between not foudn and malloc fail??
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

t_bool	no_children_needed(t_command *commands)
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

// Finds executable path,
int	handle_command(t_shell *core, pid_t *children, int **pipes,
	t_command *command)
{
	char	*exe_path;

	if (access(command->cmd_name, X_OK) == SUCCESS || is_builtin(command))
	{
		exe_path = ft_strdup(command->cmd_name); // malloc
		if (!exe_path)
		{
			core->cur_process.error_index = MALLOC_FAIL;
			return (MALLOC_FAIL);
		}
	}
	else
	{
		exe_path = find_exe_path(core, command); // malloc
	}
	if (!exe_path)
	{
		// TODO: print error and return
		ft_putstr_fd(ERROR_SHROOM, 2);
		ft_putstr_fd(command->cmd_name, 2);
		ft_putstr_fd(": no such shroom🐛\n", 2);
		return (SUCCESS);
	}
	// create a child process
	ft_putstr_fd("exe_path: ", 2);
	ft_putstr_fd(exe_path, 2);
	ft_putstr_fd("\n", 2);
	children[command->index] = fork();
	if (!children[command->index])
		handle_child(command, pipes, core, exe_path);
	// We should never get here...think of how to handle these return values
	free(exe_path);
	return (SUCCESS);
}

// Pipe and child init
int	prepare_pipes_and_children(t_shell *core, int ***pipes, pid_t **children,
int len)
{
	*pipes = malloc_pipes(len - 1); // malloc
	if (!(*pipes))
	{
		core->cur_process.error_index = MALLOC_FAIL;
		return (MALLOC_FAIL);
	}
	if (open_pipes(*pipes) != SUCCESS)
	{
		core->cur_process.error_index = PIPE_FAIL;
		free(pipes);
		return (PIPE_FAIL);
	}
	*children = ft_calloc(sizeof(pid_t), len);
	/* *children = malloc(sizeof(pid_t) * len); */
	if (!(*children))
	{
		core->cur_process.error_index = MALLOC_FAIL;
		free(pipes);
		return (MALLOC_FAIL);
	}
	return (SUCCESS);
}

// Pipe and child cleanup
int	finalise_pipes_and_children(int **pipes, pid_t *children, int len)
{
	int			ret;

	close_pipes(pipes);
	ret = wait_for_children(children, len);
	free_pipes(pipes);
	free(children);
	return (ret);
}

// Create pipes and children, handle each command, clean up
int	execute_pipeline(t_shell *core, t_command *commands)
{
	int			**pipes;
	t_command	*curr_command;
	pid_t		*children;
	int			len;
	int			ret;
	
	len = list_len(commands);
	ret = prepare_pipes_and_children(core, &pipes, &children, len); // malloc
	if (ret != SUCCESS)
	{
		finalise_pipes_and_children(pipes, children, len);
		return (ret);
	}
	curr_command = commands;
	while (curr_command)
	{
		ret = handle_command(core, children, pipes, curr_command);
		if (ret != SUCCESS)
		{
			ft_putstr_fd("handle_command failed\n", 2);
			finalise_pipes_and_children(pipes, children, len);
			return (ret);
		}
		curr_command = curr_command->next;
	}
	return (finalise_pipes_and_children(pipes, children, len));
}

// If creating child processes is not needed, just execute the command.
// Otherwise execute pipeline
int	pipeline_execution(t_shell *core, t_command *commands)
{
	if (no_children_needed(commands))
	{
		ft_putstr_fd("no children needed\n", 2);
		return (run_builtin(core, commands));
	}
	else
		return (execute_pipeline(core, commands));
}
