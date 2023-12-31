/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   form_pipeline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvagapov <vvagapov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 16:34:16 by vvagapov          #+#    #+#             */
/*   Updated: 2023/09/18 16:34:18 by vvagapov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_bool	incorrect_token_in_pipeline(t_token *current, \
	t_token *end, int *error_index)
{
	if (current == end)
	{
		*error_index = current->position;
		return (TRUE);
	}
	while (current != end)
	{
		if (current->type != WORD && !is_redir(current->type))
		{
			*error_index = current->position;
			return (TRUE);
		}
		current = current->next;
	}
	return (FALSE);
}

t_pipeline	*form_pipeline_node(t_pipeline *head_pipe, \
	t_token *end_token, t_token *head_token, int *error_index)
{
	t_pipeline	*new;
	t_pipeline	*current;

	if (incorrect_token_in_pipeline(head_token, end_token, error_index))
		return (head_pipe);
	new = malloc(sizeof(t_pipeline));
	if (!new)
	{
		*error_index = MALLOC_FAIL;
		return (head_pipe);
	}
	new->start = head_token;
	new->end = end_token;
	new->next = NULL;
	if (!head_pipe)
		return (new);
	current = head_pipe;
	while (current->next)
		current = current->next;
	current->next = new;
	return (head_pipe);
}

void	check_last_segment(t_token *last, t_token *head, int *error_index)
{
	incorrect_token_in_pipeline(head, last->next, error_index);
	if (*error_index == head->position)
		;
	else if (node_at_index(head, *error_index)
		&& node_at_index(head, *error_index)->type == AMPERSAND)
		;
	else if (*error_index == last->position && last->type != RPAR)
	{
		if (!last->next)
			*error_index = UNEXPECTED_NL;
		else
			*error_index = last->next->position;
	}
}

t_pipeline	*form_pipeline(t_token *head_token, int end_index, int *error_index)
{
	t_token		*current_token;
	t_pipeline	*head_pipe;

	current_token = head_token;
	head_pipe = NULL;
	while (current_token->next && current_token->next->position < end_index)
	{
		if (current_token->type == PIPE)
		{
			head_pipe = form_pipeline_node(head_pipe, \
			current_token, head_token, error_index);
			head_token = current_token->next;
		}
		current_token = current_token->next;
		if (*error_index != DEFAULT)
			return (empty_pipeline_list(head_pipe), NULL);
	}
	check_last_segment(current_token, head_token, error_index);
	if (*error_index != DEFAULT)
		return (empty_pipeline_list(head_pipe), NULL);
	head_pipe = form_pipeline_node(head_pipe, \
	current_token->next, head_token, error_index);
	return (head_pipe);
}
