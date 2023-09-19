/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvagapov <vvagapov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 11:29:26 by nlonka            #+#    #+#             */
/*   Updated: 2023/09/19 08:24:22 by vvagapov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	complain(void)
{
	ft_putendl_fd("Running scripts is not supported", STDERR_FILENO);
	ft_putendl_fd("Please upgrade to a better shell program", STDERR_FILENO);
	return (37);
}

void	readline_pretty(t_shell *core)
{
	char	*tmp;
	char	*fancy_prompt;

	core->cur_process.input_line = NULL;
	fancy_prompt = get_fancy_prompt(core->cur_process.ret);
	if (!fancy_prompt)
	{
		if (core->cur_process.ret)
			tmp = readline(MINI_SHROOM R "> "C);
		else
			tmp = readline(MINI_SHROOM G "> "C);
	}
	else
		tmp = readline(fancy_prompt);
	if (fancy_prompt)
		free(fancy_prompt);
	core->cur_process.input_line = tmp;
}

int	main(int ac, char **av, char **ev)
{
	t_shell	core;

	if (ac != 1 && av[0])
		return (complain());
	set_start_data(&core, ev);
	while (core.cur_process.shroom_time)
	{
		set_input_mode(&core, ON);
		readline_pretty(&core);
		set_input_mode(&core, OFF);
		if (core.cur_process.input_line)
		{
			process_line(&core, core.cur_process.input_line);
			add_to_history(core.cur_process.input_line, &core);
			free(core.cur_process.input_line);
		}
		else
			ctrl_d_handler(&core);
	}
	handle_exit(&core);
	return (core.cur_process.ret);
}
