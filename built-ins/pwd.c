/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvagapov <vvagapov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 21:24:53 by vvagapov          #+#    #+#             */
/*   Updated: 2023/09/18 21:09:52 by vvagapov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pwd(t_shell *core)
{
	char	*res;
	
	res = NULL;
	res = getcwd(res, 0);
	if (!res)
	{
		ft_putstr_fd("error retrieving current directory\n", 2);
		return (1);
	}
	ft_putstr_fd(res, STDOUT_FILENO);
	ft_putstr_fd("\n", STDOUT_FILENO);
	free(res);
	return (0);
}
