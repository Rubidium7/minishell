

#include "minishell.h"

t_ast	*make_command_node(t_token *start, t_ast *up, int end_index, int *error_index)
{
	t_ast		*new;
	t_pipeline	*pipeline;

	if (*error_index == MALLOC_FAIL)
		return (NULL);
	pipeline = form_pipeline(start, end_index, error_index);
	if (!pipeline)
		return (NULL);
	new = new_ast_node(up, pipeline, PIPE, error_index);
	if (!new)
		return (NULL);
	return (new);
}

t_token	*remove_braces(t_token *start, t_token *end, int *error_index)
{
	t_token	*new_start;

	new_start = start;
	if (start->type != LPAR || start->type != WORD || !is_redir(start->type))
		return (handle_error_value(error_index, start->position), NULL);
	if (start->type == LPAR)
	{
		new_start = start->next;
		end = last_node(start, end);
		if (end->type != RPAR)
			return (handle_error_value(error_index, start->position), NULL);
	}
	return (new_start);
}

t_ast	*left_branch(t_token *start, t_ast *up, int end_index, int *error_index)
{
	t_token	*new_start;

	if (start->position == end_index)
		return (handle_error_value(error_index, end_index), NULL);
	new_start = remove_braces(start, node_at_index(start, end_index), error_index);
	if (!new_start)
		return (NULL);
	if (new_start == start)
}

t_ast	*right_branch(t_token *start, t_ast *up, int end_index, int *error_index)
{

}

t_ast	*form_tree(t_token *start, t_ast *up, int end_index, int *error_index)
{
	t_ast	*new;
	int		index;

	if (*error_index == MALLOC_FAIL)
		return (NULL);
	index = find_logic_token(start, end_index);
	if (index == NO_LOGIC)
		return (make_command_node(start, up, end_index, error_index));
	new = new_ast_node(up, NULL, node_at_index(start, index)->type, error_index);
	if (!new)
		return (NULL);
	new->left = left_branch(start, new, index, error_index);
	new->right = right_branch(start, new, end_index, error_index);
	return (new);
}