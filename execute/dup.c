/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvagapov <vvagapov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 21:47:40 by vvagapov          #+#    #+#             */
/*   Updated: 2023/09/12 22:36:39 by vvagapov         ###   ########.fr       */
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
/* 	ft_putstr_fd(command->cmd_name, 2); //debug
	ft_putstr_fd("[", 2);
	ft_putnbr_fd(command->index, 2);
	ft_putstr_fd("]", 2);
	ft_putstr_fd(" in: ", 2);
	ft_putnbr_fd(in_fd, 2);
	ft_putstr_fd("\n", 2); */
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
/* 	ft_putstr_fd(command->cmd_name, 2); //debug
	ft_putstr_fd("[", 2);
	ft_putnbr_fd(command->index, 2);
	ft_putstr_fd("]", 2);
	ft_putstr_fd(" out: ", 2);
	ft_putnbr_fd(out_fd, 2);
	ft_putstr_fd("\n", 2); */
	return (dup2(out_fd, STDOUT_FILENO));
}
