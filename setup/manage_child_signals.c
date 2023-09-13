

#include "minishell.h"

void	child_ctrl_c(int signum)
{
	(void)signum;
	exit(130);
}

void	child_ctrl_slash(int signum)
{
	(void)signum;
	exit(131);
}

void	set_child_signals(void)
{
	struct sigaction	child_c;
	struct sigaction	child_slash;

	ft_bzero(&child_c, sizeof(child_c));
	child_c.sa_handler = child_ctrl_c;
	sigemptyset(&child_c.sa_mask);
	sigaction(SIGINT, &child_c, NULL);
	ft_bzero(&child_slash, sizeof(child_slash));
	child_slash.sa_handler = child_ctrl_slash;
	sigemptyset(&child_slash.sa_mask);
	sigaction(SIGQUIT, &child_slash, NULL);
}

int	process_exit_status(int ret, t_shell *core)
{
	core->cur_process.terminated = FALSE;
	if (ret < 0)
		;
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
		ft_putstr_fd("\n", 2);
	if (signum == 131)
		ft_putstr_fd("Quit: 3\n", 2);
	if (signum == 134)
		ft_putstr_fd("Abort trap: 6\n", 2);
	if (signum == 138)
		ft_putstr_fd("Bus error: 10\n", 2);
	if (signum == 139)
		ft_putstr_fd("Segmentation fault: 11\n", 2);
}