/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvagapov <vvagapov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 21:27:32 by vvagapov          #+#    #+#             */
/*   Updated: 2023/09/13 13:03:59 by vvagapov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	open_pipes(int **pipes)
{
	int	i;

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
	while (*pipes)
	{
		close((*pipes)[0]);
		close((*pipes)[1]);
		pipes++;
	}
}
