/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_signals.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvagapov <vvagapov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 16:34:45 by vvagapov          #+#    #+#             */
/*   Updated: 2023/09/18 16:39:36 by vvagapov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_heredoc_signals(void)
{
	struct sigaction	ignored;
	struct sigaction	ctrl_c;

	ft_bzero(&ignored, sizeof(ignored));
	ignored.sa_handler = SIG_IGN;
	sigemptyset(&ignored.sa_mask);
	sigaction(SIGQUIT, &ignored, NULL);
	ft_bzero(&ctrl_c, sizeof(ctrl_c));
	ctrl_c.sa_handler = heredoc_ctrl_c_handler;
	sigemptyset(&ctrl_c.sa_mask);
	sigaction(SIGINT, &ctrl_c, NULL);
}

void	set_heredoc_mode(t_shell *core, int mode)
{
	if (mode == ON)
	{
		set_heredoc_signals();
		tcsetattr(STDIN_FILENO, TCSAFLUSH, &core->term.new);
	}
	if (mode == OFF)
	{
		ignore_signals();
		tcsetattr(STDIN_FILENO, TCSAFLUSH, &core->term.old);
	}
}
