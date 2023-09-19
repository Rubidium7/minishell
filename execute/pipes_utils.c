/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvagapov <vvagapov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 21:27:32 by vvagapov          #+#    #+#             */
/*   Updated: 2023/09/19 08:28:51 by vvagapov         ###   ########.fr       */
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
	while (pipes[i] && pipes[i][0] != NOT_PIPE)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
		i++;
	}
}
