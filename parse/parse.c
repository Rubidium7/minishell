/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlonka <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 10:32:51 by nlonka            #+#    #+#             */
/*   Updated: 2023/08/14 10:33:03 by nlonka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parse(t_shell *core)
{
	core->cur_process.tree = syntax_check(core->tokens->next, core);
	if (!core->cur_process.tree)
		return ;
	core->cur_process.ret = 0;
	//print_tree_in_execution_order(core->cur_process.tree); //debug
	//(new, pipeline, core)
	if (go_through_heredocs(core->cur_process.tree, core))
	{
		free_tree(core->cur_process.tree);
		core->cur_process.tree = NULL;
		if (core->cur_process.error_index == MALLOC_FAIL
			|| core->cur_process.error_index == OPEN_ERROR)
			error_print(PARSE_ERROR);
	}
	print_heredocs(core->cur_process.tree, ON); //debug
	update_error_value(core);
}
