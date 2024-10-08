/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handlers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvagapov <vvagapov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 18:28:00 by nlonka            #+#    #+#             */
/*   Updated: 2023/09/19 08:20:59 by vvagapov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	heredoc_ctrl_c_handler(int signum)
{
	(void)signum;
	ft_putstr_fd("\n", STDOUT_FILENO);
	exit (1);
}

void	ctrl_c_handler(int signum)
{
	(void)signum;
	ioctl(0, TIOCSTI, "\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	g_sigint_received = TRUE;
}

void	ctrl_d_handler(t_shell *core)
{
	write(2, "exit\n", 5);
	handle_exit(core);
	exit(core->cur_process.ret);
}
