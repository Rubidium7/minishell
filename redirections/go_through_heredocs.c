/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   go_through_heredocs.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvagapov <vvagapov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 16:34:40 by vvagapov          #+#    #+#             */
/*   Updated: 2023/09/18 16:34:42 by vvagapov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_heredoc	*make_heredoc_list(t_pipeline *current, t_shell *core)
{
	t_heredoc	*head;
	t_heredoc	*current_doc;
	int			index;

	index = 0;
	head = NULL;
	while (current)
	{
		if (!head)
		{
			head = open_heredocs(current, index, core);
			current_doc = head;
		}
		else
		{
			current_doc->next = open_heredocs(current, index, core);
			if (current_doc->next)
				current_doc = current_doc->next;
		}
		if (core->cur_process.error_index != SUCCESS)
			return (empty_heredoc_list(head), NULL);
		index++;
		current = current->next;
	}
	return (head);
}

t_heredoc	*remove_heredoc_node(t_heredoc *head, int index)
{
	t_heredoc	*current;
	t_heredoc	*tmp;

	current = head;
	if (head && head->index == index)
	{
		head = head->next;
		free(current);
		return (head);
	}
	while (current && current->next && current->next->index != index)
		current = current->next;
	if (!current || !current->next)
		return (head);
	tmp = current->next;
	current->next = current->next->next;
	free(tmp);
	return (head);
}


t_heredoc	*purge_heredoc_list(t_heredoc *head, t_pipeline *current)
{
	t_token	*current_token;
	int		use_heredoc;
	int		index;

	use_heredoc = YES;
	index = 0;
	while (current)
	{
		current_token = current->start;
		while (current_token != current->end)
		{
			if (current_token->type == RED_IN)
				use_heredoc = NO;
			if (current_token->type == HEREDOC)
				use_heredoc = YES;
			current_token = current_token->next;
		}
		if (use_heredoc == NO)
			head = remove_heredoc_node(head, index);
		index++;
		current = current->next;
	}
	return (head);
}

t_bool	go_through_heredocs(t_ast *tree, t_shell *core)
{
	if (core->cur_process.error_index != SUCCESS)
		return (TRUE);
	if (!tree)
		return (FALSE);
	go_through_heredocs(tree->left, core);
	go_through_heredocs(tree->right, core);
	if (tree->pipeline)
	{
		tree->heredoc_list = make_heredoc_list(tree->pipeline, core);
		tree->heredoc_list = 
			purge_heredoc_list(tree->heredoc_list, tree->pipeline);
	}
	if (core->cur_process.error_index != SUCCESS)
		return (TRUE);
	return (FALSE);
}
