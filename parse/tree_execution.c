/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_execution.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvagapov <vvagapov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 18:41:58 by vvagapov          #+#    #+#             */
/*   Updated: 2023/09/13 18:43:14 by vvagapov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_node(t_ast *tree, t_shell *core)
{
	tree->command_list = 
		form_command_list(tree->pipeline, core, tree->heredoc_list);
	if (tree->command_list)
	{
		tree->return_value = pipeline_execution(core, tree->command_list);
		core->cur_process.ret = tree->return_value;
		if (core->cur_process.terminated)
			print_terminating_signal(core->cur_process.ret);
	}
}

int	execute_tree(t_ast *tree, t_shell *core)
{
	int	ret;

	if (core->cur_process.error_index != DEFAULT || !tree)
		return (FAILURE);
	ret = execute_tree(tree->left, core);
	if (ret && tree->type == OR)
		return (execute_tree(tree->right, core));
	else if (tree->type == OR)
		return (SUCCESS);
	if (!ret && tree->type == AND)
		return (execute_tree(tree->right, core));
	else if (tree->type == AND)
		return (FAILURE);
	if (tree->pipeline)
		execute_node(tree, core);
	if (tree->up)
		tree->up->return_value = tree->return_value;
	return (tree->return_value);
}
