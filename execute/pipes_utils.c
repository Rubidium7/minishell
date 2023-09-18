/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvagapov <vvagapov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 21:27:32 by vvagapov          #+#    #+#             */
/*   Updated: 2023/09/18 20:50:15 by vvagapov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	open_pipes(int **pipes)
{
	int	i;

	if (!pipes)
		return (SUCCESS);
	i = 0;
	while (pipes[i])
	{
		if (pipe(pipes[i]) == -1)
		{
			return (PIPE_FAIL);
		}
		i++;
	}
	return (SUCCESS);
}

void	close_pipes(int **pipes)
{
	int	i;

	if (!pipes)
		return ;
	i = 0;
	while (pipes[i] && pipes[i][0] != -1)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
		i++;
	}
	//ft_putnbr_fd(i, 2);
	//ft_putstr_fd(" - i at which close pipes stopped\n", 2);
}
