
#include "minishell.h"


int	count_words(t_token *current, t_token *end)
{
	int	amount;

	amount = 0;
	while (current != end)
	{
		if (current->type == WORD)
			amount++;
	}
	return (amount);
}

t_bool	fill_command_array(char **array, t_token *current, t_token *end)
{
	int	index;

	index = 0;
	while (current != end)
	{
		if (current->type == WORD)
		{
			array[index] = ft_strdup(current->content);
			if (!array[index])
				return (TRUE);
			index++;
		}
		current = current->next;
	}
	array[index] = NULL;
	return (FALSE);
}

t_command	*form_command_list(t_pipeline *pipeline, t_shell *core)
{
	t_command	*new;
	int			size;
	int			error_safe;

	error_safe = core->cur_process.error_index;
	core->cur_process.error_index = MALLOC_FAIL;
	size = count_words(pipeline->start, pipeline->end);
	new = malloc(sizeof(t_command));
	if (!new)
		return (NULL);
	new->heredoc_file = NULL;
	new->red_in = DEFAULT;
	new->red_out = DEFAULT;
	new->cmd_ar = malloc(sizeof(char *) * (size + 1));
	if (!new->cmd_ar)
		return (free(new), NULL);
	if (!fill_command_array(new->cmd_ar, pipeline->start, pipeline->end))
		return (free_ar(new->cmd_ar), free(new), NULL);
	new->cmd_name = ft_strdup(new->cmd_ar[0]); //we can decide if this should be malloced or not
	if (!new->cmd_name)
		return (free_ar(new->cmd_ar), free(new), NULL);
	//open_redirections(new, pipeline, core);
	return (new);
}

t_bool	format_commands(t_ast *tree, t_shell *core)
{
	if (core->cur_process.error_index)
		return (TRUE);
	if (!tree)
		return (FALSE);
	format_commands(tree->left, core);
	format_commands(tree->right, core);
	if (tree->pipeline)
		tree->command_list = form_command_list(tree->pipeline, core);
	if (core->cur_process.error_index)
		return (TRUE);
	return (FALSE);
}