/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvagapov <vvagapov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 21:24:53 by vvagapov          #+#    #+#             */
/*   Updated: 2023/09/18 21:56:57 by vvagapov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pwd(void)
{
	char	*res;
	
	res = NULL;
	res = getcwd(res, 0);
	if (!res)
	{
		print_generic_error("pwd", "getcwd",
			"error retrieving current directory");
		return (1);
	}
	ft_putstr_fd(res, STDOUT_FILENO);
	ft_putstr_fd("\n", STDOUT_FILENO);
	free(res);
	return (0);
}
