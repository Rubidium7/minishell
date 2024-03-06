/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_child_signals.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvagapov <vvagapov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 13:16:15 by vvagapov          #+#    #+#             */
/*   Updated: 2023/09/19 08:30:07 by vvagapov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_child_signals(void)
{
	struct sigaction	child_c;
	struct sigaction	child_slash;

	ft_bzero(&child_c, sizeof(child_c));
	sigemptyset(&child_c.sa_mask);
	sigaction(SIGINT, &child_c, NULL);
	ft_bzero(&child_slash, sizeof(child_slash));
	sigemptyset(&child_slash.sa_mask);
	sigaction(SIGQUIT, &child_slash, NULL);
}

int	process_exit_status(int ret, t_shell *core)
{
	core->cur_process.terminated = FALSE;
	if (ret < 0)
	{
		error_print(EXEC_ERROR);
		if (ret == MALLOC_FAIL)
			return (MALLOC_ERROR);
		if (ret == PIPE_FAIL)
			return (PIPE_ERROR);
	}
	else if (WIFEXITED(ret))
		ret = WEXITSTATUS(ret);
	else if (WIFSIGNALED(ret))
	{
		ret = WTERMSIG(ret);
		ret += 128;
		core->cur_process.terminated = TRUE;
	}
	return (ret);
}

void	print_terminating_signal(int signum)
{
	if (signum == 130)
		ft_putstr_fd("\n", STDERR_FILENO);
	else if (signum == 131)
		ft_putstr_fd("Quit: 3\n", STDERR_FILENO);
	else if (signum == 134)
		ft_putstr_fd("Abort trap: 6\n", STDERR_FILENO);
	else if (signum == 137)
		ft_putstr_fd("Killed: 9\n", STDERR_FILENO);
	else if (signum == 138)
		ft_putstr_fd("Bus error: 10\n", STDERR_FILENO);
	else if (signum == 139)
		ft_putstr_fd("Segmentation fault: 11\n", STDERR_FILENO);
	else
	{
		ft_putstr_fd("Process terminated by an unhandled signal: ",
			STDERR_FILENO);
		ft_putnbr_fd(signum - 128, STDERR_FILENO);
		ft_putendl_fd("\nPlease upgrade to a better shell program",
			STDERR_FILENO);
	}
}
