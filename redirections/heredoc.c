

#include "minishell.h"

static t_heredoc	*replace_old(t_heredoc *new)
{
	if (new)
	{
		free(new->filename);
		free(new);
	}
	new = malloc(sizeof(t_heredoc));
	return (new);
}

t_heredoc	*heredoc(t_token *current, t_heredoc *new, int index, t_shell *core)
{
	int	fd;

	core->cur_process.error_index = MALLOC_FAIL;
	new = replace_old(new);
	if (!new)
		return (NULL);
	new->filename = \
	create_heredoc_file(core->cur_process.heredoc_index, core);
	if (!new->filename)
		return (free(new), NULL);
	core->cur_process.heredoc_index++;
	new->index = index;
	new->next = NULL;
	fd = open(new->filename, O_CREAT | O_WRONLY, 0000644);
	if (fd < 0)
	{
		core->cur_process.error_index = OPEN_ERROR;
		return (free(new->filename), free(new), NULL);
	}
	core->cur_process.error_index = SUCCESS;
	return (heredoc_input(fd, current->filename, !current->quote, core), new);
}

t_heredoc	*open_heredocs(t_pipeline *pipeline, int index, t_shell *core)
{
	t_heredoc	*new;
	t_token		*current;

	current = pipeline->start;
	new = NULL;
	while (current != pipeline->end)
	{
		if (current->type == HEREDOC)
		{
			new = heredoc(current, new, index, core);
			if (core->cur_process.error_index != SUCCESS)
				return (free(new->filename), free(new), NULL);
		}
		current = current->next;
	}
	return (new);
}
