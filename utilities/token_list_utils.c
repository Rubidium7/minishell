/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_list_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvagapov <vvagapov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 15:17:38 by nlonka            #+#    #+#             */
/*   Updated: 2023/09/18 12:28:23 by vvagapov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*remove_from_token_list(t_token *head, t_token *target)
{
	t_token	*current;
	t_token	*tmp;

	if (!head || !target)
		return (head);
	current = head;
	if (target == head)
	{
		head = head->next;
		if (current->content)
			free(current->content);
		free(current);
		return (head);
	}
	while (current && current->next != target)
		current = current->next;
	if (!current)
		return (head);
	tmp = current->next;
	current->next = current->next->next;
	if (tmp->content)
		free(tmp->content);
	free(tmp);
	return (head);
}

t_token	*last_token(t_token *current)
{
	while (current && current->next)
		current = current->next;
	return (current);
}

int	find_token(t_token *current, int end_index, t_token_type type)
{
	while (current && current->position != end_index && current->type != type)
		current = current->next;
	if (!current || current->position == end_index || current->type != type)
		return (NOT_FOUND);
	return (current->position);
}

void	free_token_node(t_token *node)
{
	if (node->filename)
		free(node->filename);
	if (node->content)
		free(node->content);
	if (node->wildcard)
		empty_wildcard_list(node->wildcard);
	free(node);
}
