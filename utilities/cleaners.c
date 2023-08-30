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
		if (current->content)
			free(current->content);
		current = current->next;
		free(prev);
	}
}

void	empty_command_list(t_command *current)
{
	t_command	*prev;

	while (current)
	{
		if (current->cmd_name)
			free(current->cmd_name);
		if (current->cmd_ar)
			free_ar(current->cmd_ar);
		if (current->red_in != DEFAULT)
			close(current->red_in);
		if (current->red_out != DEFAULT)
			close(current->red_in);
		if (current->heredoc_file)
		{
			unlink(current->heredoc_file);
			free(current->heredoc_file);
		}
		prev = current;
		current = current->next;
		free(prev);
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