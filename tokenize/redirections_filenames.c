

#include "minishell.h"

t_bool	save_redirection_filenames(t_token *current)
{
	t_token	*tmp;

	while (current)
	{
		if (is_redir(current->type))
		{
			current->filename = current->next->content;
			tmp = current->next;
			current->next = current->next->next;
			free(tmp);
		}
		current = current->next;
	}
	return (FALSE);
}