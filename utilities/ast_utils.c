
#include "minishell.h"

t_ast	*new_ast_node(t_ast *up, t_token *token,\
	t_ast_type type, t_token_type separator)
{
	t_ast	*new;

	new = malloc(sizeof(ast));
	if (!new)
		return (NULL);
	new->right = NULL;
	new->left = NULL;
	new->token = token;
	new->type = type;
	if (separator != EMPTY)
		new->separator = separator;
	return (new)
}

t_token	*find_last_node(t_ast *head)
{
	while (head->left)
		head = head->left;
	if (head->right)
		return (head->right->token);
	return (head->token);
}