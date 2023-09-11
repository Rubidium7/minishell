

#include "minishell.h"

static t_token	*mark_my_words(t_token *current, t_token_type redir_type)
{
	if (current && current->type == WHITESPACE)
		current = current->next;
	while (current && current->type == WORD)
	{
		current->after_redir = redir_type;
		current = current->next;
	}
	return (current);
}

void	mark_redirections(t_token *current)
{
	t_token_type	type;

	type = HEAD;
	while (current)
	{
		if (is_redir(current->type))
		{
			type = current->type;
			current = current->next;
			continue ;
		}
		if (is_redir(type))
			current = mark_my_words(current, type);
		else
			current = current->next;
		type = HEAD;
	}
}

void	save_redirection_filenames(t_token *current)
{
	t_token	*tmp;

	while (current)
	{
		if (is_redir(current->type))
		{
			if (current->next && current->next->type == WORD)
			{
				current->ambiguity = current->next->ambiguity;
				current->filename = current->next->content;
				current->quote += current->next->quote;
				tmp = current->next;
				current->next = current->next->next;
				free(tmp);
			}
		}
		current = current->next;
	}
}