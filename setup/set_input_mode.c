/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_input_mode.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvagapov <vvagapov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 18:45:08 by nlonka            #+#    #+#             */
/*   Updated: 2023/09/09 18:37:23 by vvagapov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_input_mode_signals(t_sig *signals)
{
	ft_bzero(&signals->ignored, sizeof(signals->ignored));
	signals->ignored.sa_handler = SIG_IGN;
	sigemptyset(&signals->ignored.sa_mask);
	sigaction(SIGQUIT, &signals->ignored, NULL);
	ft_bzero(&signals->ctrl_c, sizeof(signals->ctrl_c));
	signals->ctrl_c.sa_handler = ctrl_c_handler;
	sigemptyset(&signals->ctrl_c.sa_mask);
	sigaction(SIGINT, &signals->ctrl_c, NULL);
}

void	ignore_signals(t_sig *signals)
{
	ft_bzero(&signals->ignored, sizeof(signals->ignored));
	signals->ignored.sa_handler = SIG_IGN;
	sigemptyset(&signals->ignored.sa_mask);
	sigaction(SIGINT, &signals->ignored, NULL);
	sigaction(SIGQUIT, &signals->ignored, NULL);
}

void	set_termios(t_terminal *term)
{
	tcgetattr(STDIN_FILENO, &term->old);
	tcgetattr(STDIN_FILENO, &term->new);
	term->new.c_lflag &= ~(ECHOCTL);
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &term->new);
}

void	set_input_mode(t_shell *core, int mode)
{
	if (mode == ON)
	{
		set_input_mode_signals(&core->signals);
		set_termios(&core->term);
	}
	if (mode == OFF)
	{
		ignore_signals(&core->signals);
		tcsetattr(STDIN_FILENO, TCSAFLUSH, &core->term.old);
	}
}
