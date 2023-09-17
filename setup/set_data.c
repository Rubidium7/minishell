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
	ft_bzero(core->history, 500);
	core->history_index = 0;
	//core->env = copy_array(start_env);
	if (array_to_env_list(start_env, core, TRUE))
		exit(SETUP_ERROR);
	core->tmp_dir = fetch_env("TMPDIR", core);
	if (fetch_history_file(core))
		core->history_saving = TRUE;
	else
		core->history_saving = FALSE;
	if (!core->history_saving)
		error_print(HISTORY_ERROR);
}
		