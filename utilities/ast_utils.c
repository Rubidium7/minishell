/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvagapov <vvagapov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 12:23:03 by vvagapov          #+#    #+#             */
/*   Updated: 2023/09/18 12:24:36 by vvagapov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ast	*new_ast_node(t_ast *up, t_pipeline *head, \
	t_token_type type, int *error_index)
{
	t_ast	*new;

	new = malloc(sizeof(t_ast));
	if (!new)
	{
		*error_index = MALLOC_FAIL;
		return (NULL);
	}
	new->right = NULL;
	new->left = NULL;
	new->up = up;
	new->pipeline = head;
	new->command_list = NULL;
	new->heredoc_list = NULL;
	new->return_value = SUCCESS;
	new->type = type;
	return (new);
}

int	previous_position(t_token *head, t_token *last)
{
	t_token	*current;

	if (!head)
		return (0);
	current = head;
	while (current && current->next != last)
		current = current->next;
	if (!current)
		return (previous_position(head, current));
	return (current->position);
}

int	token_after_parentheses(t_token *current, int end_index)
{
	int	parentheses;
	int	start;

	parentheses = 0;
	start = current->position;
	while (current && current->position != end_index)
	{
		if (current->type == LPAR)
			parentheses++;
		else if (current->type == RPAR)
		{
			parentheses--;
			if (parentheses == 0)
			{
				if (!current->next)
					return (UNEXPECTED_NL);
				return (current->next->position);
			}
		}
		current = current->next;
	}
	return (start);
}
