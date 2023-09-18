

#include "minishell.h"

void	empty_wildcard_list(t_wildcard *current)
{
	t_wildcard	*prev;

	while (current)
	{
		if (current->str)
			free(current->str);
		prev = current;
		current = current->next;
		free(prev);
	}
}

void	empty_token_list(t_token *current)
{
	t_token	*prev;

	while (current)
	{
		prev = current;
		current = current->next;
		free_token_node(prev);
	}
}

void	empty_heredoc_list(t_heredoc *current)
{
	t_heredoc	*tmp;

	while (current)
	{
		unlink(current->filename);
		free(current->filename);
		tmp = current;
		current = current->next;
		free(tmp);
	}
}

void	empty_command_list(t_command *current)
{
	t_command	*prev;

	while (current)
	{
		prev = current;
		current = current->next;
		free_command_node(prev);
	}
}

void	empty_pipeline_list(t_pipeline *current)
{
	t_pipeline	*prev;

	while (current)
	{
		prev = current;
		current = current->next;
		free(prev);
	}
}
