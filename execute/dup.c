/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvagapov <vvagapov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 21:47:40 by vvagapov          #+#    #+#             */
/*   Updated: 2023/09/18 13:47:15 by vvagapov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	dup_input(t_command *command, int **pipes)
{
	int			in_fd;

	if (command->red_in == DEFAULT)
	{
		if (is_first_command(command))
			return (STDIN_FILENO);
		else
			in_fd = pipes[command->index - 1][0];
	}
	else
	{
		in_fd = command->red_in;
	}
	return (dup2(in_fd, STDIN_FILENO));
}

int	dup_output(t_command *command, int **pipes)
{
	int			out_fd;

	if (command->red_out == DEFAULT)
	{
		if (is_last_command(command))
			return (STDOUT_FILENO);
		else
			out_fd = pipes[command->index][1];
	}
	else
	{
		out_fd = command->red_out;
	}
	return (dup2(out_fd, STDOUT_FILENO));
}
