

#include "minishell.h"

void	child_ctrl_c(int signum)
{
	(void)signum;
	ft_putstr_fd("\n", 2);
	exit(130);
}

void	child_ctrl_slash(int signum)
{
	(void)signum;
	ft_putstr_fd("Quit: 3\n", 2);
	exit(131);
}

void	set_child_signals(t_sig *signals)
{
	ft_bzero(&signals->child_c, sizeof(signals->child_c));
	signals->child_c.sa_handler = child_ctrl_c;
	sigemptyset(&signals->child_c.sa_mask);
	sigaction(SIGINT, &signals->child_c, NULL);
	ft_bzero(&signals->child_slash, sizeof(signals->child_slash));
	signals->child_slash.sa_handler = child_ctrl_slash;
	sigemptyset(&signals->child_slash.sa_mask);
	sigaction(SIGQUIT, &signals->child_slash, NULL);
}