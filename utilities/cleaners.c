/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaners.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlonka <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 17:13:27 by nlonka            #+#    #+#             */
/*   Updated: 2023/08/15 18:55:57 by nlonka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	empty_token_list(t_token *current)
{
	t_token	*prev;

	while (current)
	{
		prev = current;
		current = current->next;
		free_token_node(prev);
	}
}

void	empty_heredoc_list(t_heredoc *current)
{
	t_heredoc	*tmp;

	while (current)
	{
		unlink(current->filename);
		free(current->filename);
		tmp = current;
		current = current->next;
		free(tmp);
	}
}

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

void	empty_command_list(t_command *current)
{
	t_command	*prev;

	while (current)
	{
		prev = current;
		current = current->next;
		free_command_node(prev);
	}
}

void	empty_pipeline_list(t_pipeline *current)
{
	t_pipeline	*prev;

	while (current)
	{
		prev = current;
		current = current->next;
		free(prev);
	}
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