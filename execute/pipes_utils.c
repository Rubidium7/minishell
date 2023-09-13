/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvagapov <vvagapov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 21:27:32 by vvagapov          #+#    #+#             */
/*   Updated: 2023/09/12 15:26:00 by vvagapov         ###   ########.fr       */
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

			return (1);
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
