/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_data.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvagapov <vvagapov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 10:33:41 by nlonka            #+#    #+#             */
/*   Updated: 2023/09/18 13:15:52 by vvagapov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	zero_history(char **history)
{
	int	i;

	i = 0;
	while (i != HISTORY_MAX)
	{
		history[i] = NULL;
		i++;
	}
}

void	set_start_data(t_shell *core, char **start_env)
{
	g_sigint_received = FALSE;
	set_termios(&core->term);
	core->cur_process.ret = 0;
	core->cur_process.shroom_time = TRUE;
	core->env_list = NULL;
	zero_history(core->history);
	core->history_index = 0;
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
