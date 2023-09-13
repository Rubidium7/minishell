/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvagapov <vvagapov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 21:24:53 by vvagapov          #+#    #+#             */
/*   Updated: 2023/09/13 15:05:06 by vvagapov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pwd(t_shell *core)
{
	char	*res;
	
	res = NULL;
	res = getcwd(res, 0); // malloc
	if (!res)
	{
		core->cur_process.error_index = MALLOC_FAIL;
		return (MALLOC_FAIL);
	}
	ft_putstr_fd(res, STDOUT_FILENO);
	ft_putstr_fd("\n", STDOUT_FILENO);
	free(res);
	return (SUCCESS);
}
