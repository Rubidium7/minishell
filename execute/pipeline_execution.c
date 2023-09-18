/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_execution.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvagapov <vvagapov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 20:06:21 by vvagapov          #+#    #+#             */
/*   Updated: 2023/09/18 20:51:41 by vvagapov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	execute_cmd(t_shell *core, t_command *command, char *exe_path)
{
	char	**env_array;

	if (is_builtin(command))
		exit(run_builtin(core, command, TRUE));
	else
	{
		env_array = env_list_to_array(core->env_list, core);
		if (!env_array)
		{
			core->cur_process.error_index = MALLOC_FAIL;
			return ;
		}
		execve(exe_path, command->cmd_ar, env_array);
	}
}

static void	handle_child(t_command *curr_command, int **pipes, t_shell *core,
	char *exe_path)
{
	set_child_signals();
	if (curr_command->red_in == NOT_OPEN 
		|| curr_command->red_out == NOT_OPEN)
		exit(1);
	if (core->cur_process.ret)
		exit(core->cur_process.ret);
	if (!exe_path)
		exit(0);
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

// Finds executable path and forks to child process to execute command
static int	handle_command(t_shell *core, pid_t *children, int **pipes,
	t_command *command)
{
	char		*exe_path;
	struct stat	file_info;

	stat(command->cmd_name, &file_info);
	if (!command->cmd_name)
		exe_path = NULL;
	else if ((access(command->cmd_name, X_OK) == SUCCESS
			&& !S_ISDIR(file_info.st_mode)) || is_builtin(command))
		exe_path = ft_strdup(command->cmd_name);
	else
		exe_path = find_exe_path(core, command);
	if (!exe_path && core->cur_process.ret != 127
		&& core->cur_process.ret != 126 && command->cmd_name)
	{
		core->cur_process.error_index = MALLOC_FAIL;
		return (MALLOC_FAIL);
	}
	children[command->index] = fork();
	if (!children[command->index])
		handle_child(command, pipes, core, exe_path);
	free(exe_path);
	return (SUCCESS);
}

// Create pipes and children, handle each command, clean up
static int	execute_pipeline(t_shell *core, t_command *commands)
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
		core->cur_process.terminated = FALSE;
		return (run_builtin(core, commands, FALSE));
	}
	else
		return (process_exit_status(execute_pipeline(core, commands), core));
}
