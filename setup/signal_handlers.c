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

void	heredoc_ctrl_c_handler(int signum)
{
	//test_file("ctrl c heredoc called\n"); //debug
	(void)signum;
	ft_putstr_fd("\n", 1);
	exit (1);
}

void	ctrl_c_handler(int signum)
{
	(void)signum;
	//test_file("ctrl c called\n"); //debug
	ioctl(0, TIOCSTI, "\n");
	rl_on_new_line();
	rl_replace_line("", 0);
}

void	ctrl_d_handler(t_shell *core)
{
	write(2, "\x1b[A", 3); // vv
	write(2, "\x1b[14C", 5); //might remove these
	write(2, "exit🍂\n", 9);
	handle_exit(core);
	exit(core->cur_process.ret);
}
