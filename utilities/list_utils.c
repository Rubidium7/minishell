
#include "minishell.h"

t_token	*remove_from_token_list(t_token *head, t_token *target)
{
	t_token	*current;
	t_token	*tmp;

	if (!head || !target)
		return (head);
	current = head;
	if (target == head)
	{
		head = head->next;
		if (current->content)
			free(current->content);
		free(current);
		return (head);
	}
	while (current && current->next != target)
		current = current->next;
	if (!current)
		return (head);
	tmp = current->next;
	current->next = current->next->next;
	if (tmp->content)
		free(tmp->content);
	free(tmp);
	return (head);
}