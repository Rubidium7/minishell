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

void	add_to_history(char *str)
{
	if (ft_strncmp(str, "", 1))
		add_history(str);
} //might be useless as a lone function

void	readline_pretty(t_shell *core)
{
	char	*tmp;

	tmp = readline("🍄"W"Mini"C R"Shroom"C"> ");
//	tmp = readline("🍄"WR"Mini"C RW"Shroom"C"> ");
	core->cur_process.input_line = tmp;
}

int main(int ac, char **av, char **ev)
{
	t_shell	core;
	(void)ac;
	(void)av;

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
