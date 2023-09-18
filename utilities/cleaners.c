/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaners.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvagapov <vvagapov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 17:13:27 by nlonka            #+#    #+#             */
/*   Updated: 2023/09/18 12:25:08 by vvagapov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_command_node(t_command *node)
{
	if (node->cmd_ar)
		free_ar(node->cmd_ar);
	if (node->red_in > 0)
		close(node->red_in);
	if (node->red_out > 0)
		close(node->red_out);
	free(node);
}

t_ast	*free_tree(t_ast *tree)
{
	if (!tree)
		return (NULL);
	if (tree->left)
		free_tree(tree->left);
	if (tree->right)
		free_tree(tree->right);
	if (tree->pipeline)
		empty_pipeline_list(tree->pipeline);
	if (tree->heredoc_list)
		empty_heredoc_list(tree->heredoc_list);
	if (tree->command_list)
		empty_command_list(tree->command_list);
	free(tree);
	return (NULL);
}

void	clean_up(t_shell *core)
{
	empty_token_list(core->tokens);
	free_tree(core->cur_process.tree);
}
