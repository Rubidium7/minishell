
#include "minishell.h"

t_ast	*new_ast_node(t_ast *up, t_token *token,\
	t_ast_type type)
{
	t_ast	*new;

	new = malloc(sizeof(t_ast));
	if (!new)
		return (NULL);
	new->right = NULL;
	new->left = NULL;
	new->token = token;
	new->type = type;
	return (new)
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