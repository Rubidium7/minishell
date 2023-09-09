/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvagapov <vvagapov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 21:47:40 by vvagapov          #+#    #+#             */
/*   Updated: 2023/09/09 21:49:47 by vvagapov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	dup_output(t_command *curr_command, int **pipes)
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
	return (dup2(out_fd, STDOUT_FILENO));
}
