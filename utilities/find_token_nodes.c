/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_token_nodes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvagapov <vvagapov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 17:58:30 by vvagapov          #+#    #+#             */
/*   Updated: 2023/09/18 18:00:23 by vvagapov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*node_at_index(t_token *current, int end_index)
{
	while (current && current->position != end_index)
		current = current->next;
	return (current);
}

t_token	*last_node(t_token *current, t_token *end)
{
	while (current->next != end)
		current = current->next;
	return (current);
}

int	find_logic_token(t_token *current, int end_index)
{
	int	index;
	int	parentheses;

	index = NO_LOGIC;
	parentheses = 0;
	while (current && current->position != end_index)
	{
		if (current->type == LPAR)
			parentheses++;
		else if (current->type == RPAR)
			parentheses--;
		else if (is_logic(current->type))
		{
			if (parentheses == 0)
				index = current->position;
			else if (index == NO_LOGIC)
				index = PARENTHESES_ERROR;
		}
		current = current->next;
	}
	return (index);
}
