/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exiting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvagapov <vvagapov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 11:31:56 by nlonka            #+#    #+#             */
/*   Updated: 2023/09/18 12:55:13 by vvagapov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_history(t_shell *core)
{
	int	i;

	i = 0;
	while (i != 500)
	{
		if (core->history[i])
		{
			free(core->history[i]);
			core->history[i] = NULL;
		}
		i++;
	}
}

int	handle_exit(t_shell *core)
{
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &core->term.old);
	add_to_history_file(core);
	clear_env_list(core->env_list);
	free(core->tmp_dir);
	free_history(core);
	return (core->cur_process.ret);
}
