
#include "minishell.h"

t_ast	*new_ast_node(t_ast *up, t_pipeline *head,\
	t_ast_type type)
{
	t_ast	*new;

	new = malloc(sizeof(t_ast));
	if (!new)
		return (NULL);
	new->first_condition = NULL;
	new->right = NULL;
	new->left = NULL;
	new->up = up;
	new->pipeline = head;
	new->type = type;
	return (new);
}

t_token	*node_at_index(t_token *current, int index)
{
	while (current && current->position != index)
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

int	find_logic_token(t_token *current)
{
	int index[2];
	int parentheses;

	index[0] = -1;
	index[1] = -1;
	parentheses = 0;
	while (current)
	{
		if (current->type == LPAR)
			parentheses++;
		else if (current->type == RPAR)
			parentheses--;	
		else if (current->type == OR || current->type == AND)
		{
			if (index[0] == -1 || index[1] > parentheses)
			{
				index[0] = current->position;
				index[1] = parentheses;
			}
		}
		current = current->next;
	}
	return (index[0]);
}