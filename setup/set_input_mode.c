/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_input_mode.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvagapov <vvagapov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 18:45:08 by nlonka            #+#    #+#             */
/*   Updated: 2023/09/17 22:54:35 by vvagapov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_input_mode_signals(void)
{
	struct sigaction	ignored;
	struct sigaction	ctrl_c;

	ft_bzero(&ignored, sizeof(ignored));
	ignored.sa_handler = SIG_IGN;
	sigemptyset(&ignored.sa_mask);
	sigaction(SIGQUIT, &ignored, NULL);
	ft_bzero(&ctrl_c, sizeof(ctrl_c));
	ctrl_c.sa_handler = ctrl_c_handler;
	sigemptyset(&ctrl_c.sa_mask);
	sigaction(SIGINT, &ctrl_c, NULL);
}

void	ignore_signals(void)
{
	struct sigaction	ignored;

	ft_bzero(&ignored, sizeof(ignored));
	ignored.sa_handler = SIG_IGN;
	sigemptyset(&ignored.sa_mask);
	sigaction(SIGINT, &ignored, NULL);
	sigaction(SIGQUIT, &ignored, NULL);
}

void	set_termios(t_terminal *term)
{
	tcgetattr(STDIN_FILENO, &term->old);
	tcgetattr(STDIN_FILENO, &term->new);
	term->new.c_lflag &= ~(ECHOCTL);
}

void	set_input_mode(t_shell *core, int mode)
{
	if (mode == ON)
	{
		set_input_mode_signals();
		tcsetattr(STDIN_FILENO, TCSAFLUSH, &core->term.new);
	}
	if (mode == OFF)
	{
		if (g_sigint_received)
			core->cur_process.ret = g_sigint_received;
		g_sigint_received = FALSE;
		ignore_signals();
		tcsetattr(STDIN_FILENO, TCSAFLUSH, &core->term.old);
	}
}
