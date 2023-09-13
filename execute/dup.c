/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvagapov <vvagapov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 21:47:40 by vvagapov          #+#    #+#             */
/*   Updated: 2023/09/13 11:46:24 by vvagapov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	dup_input(t_command *command, int **pipes)
{
	int			in_fd;

/* 	ft_putstr_fd(command->cmd_name, 2); //debug
	ft_putstr_fd("[", 2);
	ft_putnbr_fd(command->index, 2);
	ft_putstr_fd("]", 2);
	ft_putstr_fd(" in before: ", 2);
	ft_putnbr_fd(command->red_in, 2);
	ft_putstr_fd("\n", 2); */
	// if the first command, no need to dup input
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
/* 	ft_putstr_fd(command->cmd_name, 2); //debug
	ft_putstr_fd("[", 2);
	ft_putnbr_fd(command->index, 2);
	ft_putstr_fd("]", 2);
	ft_putstr_fd(" in after: ", 2);
	ft_putnbr_fd(in_fd, 2);
	ft_putstr_fd("\n", 2); */
	return (dup2(in_fd, STDIN_FILENO));
}

int	dup_output(t_command *command, int **pipes)
{
	int			out_fd;

/* 	ft_putstr_fd(command->cmd_name, 2); //debug
	ft_putstr_fd("[", 2);
	ft_putnbr_fd(command->index, 2);
	ft_putstr_fd("]", 2);
	ft_putstr_fd(" out before: ", 2);
	ft_putnbr_fd(command->red_out, 2);
	ft_putstr_fd("\n", 2); */
	// if the last command, no need to dup output
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
/* 	ft_putstr_fd(command->cmd_name, 2); //debug
	ft_putstr_fd("[", 2);
	ft_putnbr_fd(command->index, 2);
	ft_putstr_fd("]", 2);
	ft_putstr_fd(" out after: ", 2);
	ft_putnbr_fd(out_fd, 2);
	ft_putstr_fd("\n", 2); */
	return (dup2(out_fd, STDOUT_FILENO));
}
