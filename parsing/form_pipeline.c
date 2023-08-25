

#include "minishell.h"

t_bool	incorrect_token_in_pipeline(t_token *current, t_token *end, int *error_index)
{
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
		*error_index = -2;
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

t_pipeline	*form_pipeline(t_token *head_token, int end_index, int *error_index)
{
	t_token 	*current_token;
	t_pipeline	*head_pipe;

	current_token = head_token;
	head_pipe = NULL;
	while (current_token && current_token->position != end_index)
	{
		if (!current_token->next || current_token->next->position == end_index)
		{
			head_pipe = form_pipeline_node(head_pipe, \
			current_token->next, head_token, error_index);
		}
		else if (current_token->type == PIPE)
		{
			head_pipe = form_pipeline_node(head_pipe, \
			current_token, head_token, error_index);
			head_token = current_token->next;
		}
		current_token = current_token->next;
		if (*error_index != -1)
			return (empty_list((t_list *)head_pipe), NULL);
	}
	return (head_pipe);
}