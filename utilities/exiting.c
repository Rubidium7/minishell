/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exiting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlonka <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 11:31:56 by nlonka            #+#    #+#             */
/*   Updated: 2023/08/21 11:32:01 by nlonka           ###   ########.fr       */
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
	free(core->tmp_dir);
	free_history(core);
	//free_ar(core->env);
	return (core->cur_process.ret);
}
