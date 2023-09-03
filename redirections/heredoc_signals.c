

#include "minishell.h"

void	set_heredoc_signals(t_sig *signals)
{
	signals->ignored.sa_handler = SIG_IGN;
	sigemptyset(&signals->ignored.sa_mask);
	sigaction(SIGQUIT, &signals->ignored, NULL);
	signals->ctrl_c.sa_handler = heredoc_ctrl_c_handler;
	sigemptyset(&signals->ctrl_c.sa_mask);
	sigaction(SIGINT, &signals->ctrl_c, NULL);
}

void	set_heredoc_mode(t_shell *core, int mode)
{
	if (mode == ON)
	{
		set_heredoc_signals(&core->signals);
		set_termios(&core->term);
	}
	if (mode == OFF)
	{
		ignore_signals(&core->signals);
		tcsetattr(STDIN_FILENO, TCSAFLUSH, &core->term.old);
	}
}