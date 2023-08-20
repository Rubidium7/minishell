/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlonka <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 09:17:54 by nlonka            #+#    #+#             */
/*   Updated: 2023/08/20 21:51:37 by nlonka           ###   ########.fr       */
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
	while (37)
	{
		set_input_mode(&core, ON);
		readline_pretty(&core);
		set_input_mode(&core, OFF);
		if (core.cur_process.input_line)
		{
		//	process_line(&core, core.cur_process.input_line);
			add_to_history(core.cur_process.input_line);
			free(core.cur_process.input_line);
		}
		else
			ctrl_d_handler(&core);
	}
	handle_exit(&core);
	return (core.cur_process.ret);
}
