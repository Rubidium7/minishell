
#include "minishell.h"

void	wildcards_in_filenames(t_token *current)
{
	t_token	*found;

	while (current)
	{
		if (is_redir(current->type) && current->type != HEREDOC)
		{
			found = find_matches(current->wildcard);
			if (found)
			{
				if (found->next)
					current->ambiguity = TRUE;
				else
				{
					free(current->filename);
					current->filename = ft_strdup(found->content);
					if (!current->filename)
						error_print(WILDCARD_ERROR);
				}
				empty_token_list(found);
			}
		}
		current = current->next;
	}
}