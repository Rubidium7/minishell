/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_data.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvagapov <vvagapov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 10:33:41 by nlonka            #+#    #+#             */
/*   Updated: 2023/09/15 19:44:36 by vvagapov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_start_data(t_shell *core, char **start_env)
{
	g_sigint_received = FALSE;
	set_termios(&core->term);
	core->cur_process.ret = 0;
	core->cur_process.shroom_time = TRUE;
	core->env_list = NULL;
	core->env = copy_array(start_env);
	if (array_to_env_list(start_env, core, TRUE))
	{
		exit(SETUP_ERROR);
	}
}
		