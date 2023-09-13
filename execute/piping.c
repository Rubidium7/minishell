/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piping.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvagapov <vvagapov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 20:06:21 by vvagapov          #+#    #+#             */
/*   Updated: 2023/09/12 22:36:41 by vvagapov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include "structs.h"
#include "minishell.h"

char	**split_path(char* path)
{
	return ft_split(path, ':');
	//https://i.kym-cdn.com/photos/images/newsfeed/001/889/888/265.jpeg
}

/* int	execute(t_shell *shell, char** paths, t_command *command)
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
} */

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

void	execute_cmd(t_shell *core, t_command *command, char *exe_path)
{
	if (is_builtin(command))
		exit(run_builtin(command));
	else
		execve(exe_path, command->cmd_ar, core->env);
}

void	handle_child(t_command *curr_command, int **pipes, t_shell *core,
	char *exe_path)
{
/*	printf("child name: %s\n", curr_command->cmd_name);  //debug
 	printf("red_in: %d\n", curr_command->red_in);
	printf("red_out: %d\n", curr_command->red_out); */
	set_child_signals(&core->signals);
	if (dup_input(curr_command, pipes) == -1
	|| dup_output(curr_command, pipes) == -1)
	{
		// the below is useless, right?
		// core->cur_process.error_index = DUP_ERROR;
		ft_putstr_fd("dup error\n", 2); //debug
		exit(1);
	}
	close_pipes(pipes);
	execute_cmd(core, curr_command, exe_path);
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
	//printf("ret = %d\n", ret); //debug
	return(WEXITSTATUS(ret));
}

// Joins the path to command name and returns the result if successful,
// Otherwise sets the error index and returns NULL
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

/* char *check_path(t_shell *core, char *path, t_command *command)
{
	char	*exe_path;

	exe_path = join_path(core, path, command->cmd_name);

} */
char	**fetch_paths_array(t_shell *core)
{
	char	*paths;
	char	**paths_split;

	paths = fetch_env("PATH", core);
	if (!paths)
	{
		// what to do in this case? anything extra?
		core->cur_process.error_index = MALLOC_FAIL;
		return (NULL);
	}
	paths_split = split_path(paths);
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

	paths_split = fetch_paths_array(core);
	if (!paths_split)
		return (NULL);
	i = 0;
	while (paths_split[i])
	{
		exe_path = join_path(core, paths_split[i], command->cmd_name);
		if (!exe_path || access(exe_path, X_OK) == SUCCESS)
		{
			/* ft_putstr_fd("exe_path exiting: ", 2);
			if (!exe_path)
				ft_putstr_fd("null", 2);
			else
				ft_putstr_fd(exe_path, 2);
			ft_putstr_fd("\n", 2); */
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
		exe_path = ft_strdup(command->cmd_name);
		if (!exe_path)
		{
			core->cur_process.error_index = MALLOC_FAIL;
			return (MALLOC_FAIL);
		}
	}
	else
	{
		exe_path = find_exe_path(core, command);
	}
	if (!exe_path)
	{
		// TODO: print error and return
		ft_putstr_fd(ERROR_SHROOM, 2);
		ft_putstr_fd(command->cmd_name, 2);
		ft_putstr_fd(": no such shroom🐛\n", 2);
		return (SUCCESS);
	}
/* 	else
	{
		ft_putstr_fd("exe_path: ", 2);
		ft_putstr_fd(exe_path, 2);
		ft_putstr_fd("\n", 2);
	} */
	// create a child process
	children[command->index] = fork();
	if (!children[command->index])
		handle_child(command, pipes, core, exe_path);
	// We should never get here...think of how to handle these return values
	return (SUCCESS);
}

// Pipe and child init
int	prepare_pipes_and_children(t_shell *core, int ***pipes, pid_t **children,
int len)
{
	*pipes = malloc_pipes(len - 1);
	if (!(*pipes))
	{
		core->cur_process.error_index = MALLOC_FAIL;
		return (MALLOC_FAIL);
	}
	if (open_pipes(*pipes) != SUCCESS)
	{
		core->cur_process.error_index = PIPE_FAIL;
		return (PIPE_FAIL);
	}
	*children = malloc(sizeof(pid_t) * len);
	if (!(*children))
	{
		core->cur_process.error_index = MALLOC_FAIL;
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
	ret = prepare_pipes_and_children(core, &pipes, &children, len);
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
		/* ft_putstr_fd("no children needed\n", 2); */
		return (run_builtin(commands));
	}
	else
		return (execute_pipeline(core, commands));
}
