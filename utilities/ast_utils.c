
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
	new->type = type;
	return (new);
}

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

int	find_node(t_token *current, t_token_type type, int end_index)
{
	while (current && current->type != type
	&& current->position != end_index)
		current = current->next;
	if (!current || current->type != type)
		return (0);
	return (current->position);
}

int	find_logic_token(t_token *current, int end_index)
{
	int index;
	int parentheses;

	index = NO_LOGIC;
	parentheses = 0;
	while (current && current->position != end_index)
	{
		if (current->type == LPAR)
			parentheses++;
		else if (current->type == RPAR)
			parentheses--;	
		else if (current->type == OR || current->type == AND)
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

// int	find_logic_token(t_token *current, int end_index)
// {
// 	int index[2];
// 	int parentheses;

// 	index[0] = DEFAULT;
// 	index[1] = DEFAULT;
// 	parentheses = 0;
// 	while (current && current->position != end_index)
// 	{
// 		if (current->type == LPAR)
// 			parentheses++;
// 		else if (current->type == RPAR)
// 			parentheses--;	
// 		else if (current->type == OR || current->type == AND)
// 		{
// 			if (index[0] == -1 || index[1] >= parentheses)
// 			{
// 				index[0] = current->position;
// 				index[1] = parentheses;
// 			}
// 		}
// 		current = current->next;
// 	}
// 	return (index[0]);
// }