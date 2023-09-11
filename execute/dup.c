/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvagapov <vvagapov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 21:47:40 by vvagapov          #+#    #+#             */
/*   Updated: 2023/09/11 23:15:03 by vvagapov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	dup_input(t_command *command, int **pipes)
{
	int			in_fd;
	
	// if the first command, no need to dup input
	if (is_first_command(command))
		return (STDIN_FILENO);
	if (command->red_in != DEFAULT)
		in_fd = command->red_in;
	else
		in_fd = pipes[command->index - 1][0];
	// printf("%s: in_fd: %d\n", command->cmd_name, in_fd); //debug
	return (dup2(in_fd, STDIN_FILENO));
}

int	dup_output(t_command *command, int **pipes)
{
	int			out_fd;

	// if the last command, no need to dup output
	if (is_last_command(command))
		return (STDOUT_FILENO);
	if (command->red_out != DEFAULT)
		out_fd = command->red_out;
	else
		out_fd = pipes[command->index][1];
	// printf("%s: out_fd: %d\n", command->cmd_name, out_fd); //debug
	return (dup2(out_fd, STDOUT_FILENO));
}
