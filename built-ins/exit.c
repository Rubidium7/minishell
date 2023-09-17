/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvagapov <vvagapov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 21:26:21 by vvagapov          #+#    #+#             */
/*   Updated: 2023/09/17 17:17:34 by vvagapov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"



long long int	ft_exit(t_shell *core, t_command *command)
{
	long long int	res;
	int				i;
	
	// no args -> return curr_process ret
	(void)core;
	(void)command;
	(void)res;
	i = 1;
	
	res = 0;
	core->cur_process.shroom_time = FALSE;
	return(res);
}
