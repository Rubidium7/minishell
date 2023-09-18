/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvagapov <vvagapov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 10:32:51 by nlonka            #+#    #+#             */
/*   Updated: 2023/09/18 00:12:36 by vvagapov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parse(t_shell *core)
{
	core->cur_process.tree = syntax_check(core->tokens->next, core);
	if (!core->cur_process.tree)
		return ;
	core->cur_process.old_ret = core->cur_process.ret;
	core->cur_process.ret = SUCCESS;
	core->cur_process.error_index = SUCCESS;
	if (go_through_heredocs(core->cur_process.tree, core))
	{
		free_tree(core->cur_process.tree);
		core->cur_process.tree = NULL;
		if (core->cur_process.error_index == MALLOC_FAIL
			|| core->cur_process.error_index == OPEN_ERROR)
			error_print(PARSE_ERROR);
	}
	update_error_value(core);
}
