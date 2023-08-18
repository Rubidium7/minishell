

#include "minishell.h"

t_bool	handle_redirections(t_token *current)
{
	while (current)
	{
		if (is_redir(current->type))
		{
			
		}
		else
			current = current->next;
	}
}