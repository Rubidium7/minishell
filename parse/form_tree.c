

#include "minishell.h"

t_ast	*make_command_node(t_token *start, t_ast *up, int end_index, int *error_index)
{
	t_ast		*new;
	t_pipeline	*pipeline;

	if (*error_index == MALLOC_FAIL)
		return (NULL);
	pipeline = form_pipeline(start, end_index, error_index);
	//printf("error %d\n", *error_index); //debug
	//print_token(start, ON); //debug
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
	if (start->type != LPAR && start->type != WORD && !is_redir(start->type))
		return (handle_error_value(error_index, start->position), NULL);
	if (start->type == LPAR)
	{
		new_start = start->next;
		end = right_brace(new_start, end);
		if (!end || end->type != RPAR)
			return (print_token(end, ON), handle_error_value(error_index, start->position), NULL);
	}
	return (new_start);
}

t_ast	*branch_out(t_token *start, t_ast *up, int end_index, int *error_index)
{
	t_token	*new_start;
	t_token	*temp;
	int		index;

	if (!start || find_logic_token(start, end_index) == start->position)
		return (handle_error_value(error_index, end_index), NULL);
	new_start = remove_braces(start, node_at_index(start, end_index), error_index);
	if (!new_start)
		return (NULL);
	if (new_start != start)
	{
		temp = right_brace(new_start, node_at_index(new_start, end_index));
		if (temp)
		{
			end_index = previous_position(new_start, temp);
			start = remove_from_token_list(start, temp);
		}
		//printf("end index is %d\n", end_index); //debug
	}
	index = find_logic_token(new_start, end_index);
	if (index == NO_LOGIC && new_start != start)
		return (handle_error_value(error_index, start->position), NULL);
	return (form_tree(new_start, up, end_index, error_index));
}

t_ast	*form_tree(t_token *start, t_ast *up, int end_index, int *error_index)
{
	t_ast	*new;
	int		index;

	if (*error_index == MALLOC_FAIL)
		return (NULL);
	index = find_logic_token(start, end_index);
	//printf("logic index is %d\n", index); //debug
	//printf("start index is %d\n", start->position); //debug
	//printf("end index is %d\n", end_index); //debug
	if (index == PARENTHESES_ERROR)
	{
		index = token_after_parentheses(start, end_index);
		return (handle_error_value(error_index, index), NULL);
	}
	if (index == NO_LOGIC)
		return (make_command_node(start, up, end_index, error_index));
	new = new_ast_node(up, NULL, node_at_index(start, index)->type, error_index);
	if (!new)
		return (NULL);
	new->left = branch_out(start, new, index, error_index);
	new->right = branch_out(node_at_index(start, index)->next, new, end_index, error_index);
	return (new);
}