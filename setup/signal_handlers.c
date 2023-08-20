/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handlers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlonka <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 18:28:00 by nlonka            #+#    #+#             */
/*   Updated: 2023/08/20 21:50:10 by nlonka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ctrl_c_handler(int signum)
{
	(void)signum;
	ioctl(0, TIOCSTI, "\n");
	rl_on_new_line();
	rl_replace_line("", 0);
}

void	ctrl_d_handler(t_shell *core)
{
	write(1, "exit\n", 5);
	handle_exit(core);
	exit(core->cur_process.ret);
}
