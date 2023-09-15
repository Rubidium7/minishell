/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlonka <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 11:29:26 by nlonka            #+#    #+#             */
/*   Updated: 2023/08/21 11:29:28 by nlonka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	complain(void)
{
	ft_putendl_fd("Running scripts is not supported", 2);
	ft_putendl_fd("Please upgrade to a better shell program", 2);
	return (37);
}

static void	add_to_history(char *str)
{
	if (ft_strncmp(str, "", 1))
		add_history(str);
} //might be useless as a lone function

int main(int ac, char **av, char **ev)
{
	t_shell	core;

	if (ac != 1 && av[0])
		return (complain());
	set_start_data(&core, ev);
	//print_ar(core.env);
	while (core.cur_process.shroom_time)
	{
		set_input_mode(&core, ON);
		readline_pretty(&core);
		set_input_mode(&core, OFF);
		if (core.cur_process.input_line)
		{
			process_line(&core, core.cur_process.input_line);
			add_to_history(core.cur_process.input_line);
			free(core.cur_process.input_line);
		}
		else
			ctrl_d_handler(&core);
	}
	handle_exit(&core); ///change this when env management has been changed!
	return (core.cur_process.ret);
}
