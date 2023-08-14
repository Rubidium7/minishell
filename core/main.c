/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlonka <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 09:17:54 by nlonka            #+#    #+#             */
/*   Updated: 2023/08/14 18:59:33 by nlonka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_to_history(char *str)
{
	if (ft_strncmp(str, "", 1))
		add_history(str);
} //might be useless as a lone function

int main(int ac, char **av, char **ev)
{
	t_shell	core;
	(void)ac;
	(void)av;

	set_start_data(&core, ev);
	while (37)
	{
		set_input_mode(&core, ON);
		core.info.input_line = readline(">");
		set_input_mode(&core, OFF);
		if (core.info.input_line)
		{
			//process_line(core, core.info.input_line);
			add_to_history(core.info.input_line);
			free(core.info.input_line);
		}
		else
			ctrl_d_handler(&core);
	}
	handle_exit(&core);
	return (core.info.ret);
}
