/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvagapov <vvagapov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 21:45:07 by vvagapov          #+#    #+#             */
/*   Updated: 2023/09/18 20:51:17 by vvagapov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	**malloc_pipes(int num)
{
	int	**res;
	int	i;

	res = malloc(sizeof(int *) * (num + 1));
	if (!res)
		return (NULL);
	res[num] = NULL;
	i = 0;
	while (i < num)
	{
		res[i] = malloc(sizeof(int) * 2);
		if (!res[i])
		{
			free(res);
			return (NULL);
		}
		i++;
	}
	return (res);
}

void	free_pipes(int **pipes)
{
	int	i;

	i = 0;
	while (pipes[i])
	{
		free(pipes[i]);
		i++;
	}
	free(pipes);
}
