/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_and_finalise_pipeline.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvagapov <vvagapov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 13:23:41 by vvagapov          #+#    #+#             */
/*   Updated: 2023/09/18 20:50:04 by vvagapov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_pipes(int **pipes, int len)
{
	int i;

	i = 0;
	while (i < len)
	{
		pipes[i][0] = -1;
		pipes[i][1] = -1;
		i++;
	}
	//ft_putnbr_fd(i, 2);
	//ft_putstr_fd(" - i at which init pipes stopped\n", 2);
}

// Pipe and child init
int	prepare_pipes_and_children(t_shell *core, int ***pipes, pid_t **children,
int len)
{
	*children = NULL;
	*pipes = malloc_pipes(len - 1);
	if (!(*pipes))
	{
		//ft_putstr_fd("malloc failed\n", 2);
		core->cur_process.error_index = MALLOC_FAIL;
		return (MALLOC_FAIL);
	}
	init_pipes(*pipes, len - 1);
	if (open_pipes(*pipes) != SUCCESS)
	{
		//ft_putstr_fd("opening pipes failed\n", 2);
		core->cur_process.error_index = PIPE_FAIL;
		return (PIPE_FAIL);
	}
	*children = ft_calloc(sizeof(pid_t), len);
	if (!(*children))
	{
		core->cur_process.error_index = MALLOC_FAIL;
		return (MALLOC_FAIL);
	}
	return (SUCCESS);
}

static int	wait_for_children(pid_t *children, int len)
{
	int	i;
	int	ret;

	if (!children)
		return (0);
	i = 0;
	ret = 0;
	while (i < len)
	{
		waitpid(children[i], &ret, 0);
		i++;
	}
	return (ret);
}

// Pipe and child cleanup
int	finalise_pipes_and_children(int **pipes, pid_t *children, int len)
{
	int			ret;

	close_pipes(pipes);
	ret = wait_for_children(children, len);
	free_pipes(pipes);
	free(children);
	return (ret);
}
