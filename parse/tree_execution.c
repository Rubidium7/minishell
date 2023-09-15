
#include "minishell.h"


int	count_words(t_token *current, t_token *end)
{
	int	amount;

	amount = 0;
	while (current != end)
	{
		if (current->type == WORD)
			amount++;
		current = current->next;
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

static void	set_values(t_command *new, int index)
{
	new->cmd_name = NULL;
	new->cmd_ar = NULL;
	new->red_in = DEFAULT;
	new->red_out = DEFAULT;
	new->index = index;
	new->next = NULL;
}

t_command	*form_command(t_pipeline *pipeline, int index, t_shell *core, t_heredoc *heredoc)
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
	set_values(new, index);
	new->cmd_ar = malloc(sizeof(char *) * (size + 1));
	if (!new->cmd_ar)
		return (free(new), NULL);
	if (fill_command_array(new->cmd_ar, pipeline->start, pipeline->end))
		return (free_ar(new->cmd_ar), free(new), NULL);
	new->cmd_name = new->cmd_ar[0]; //we can decide if this should be malloced or not
	core->cur_process.error_index = error_safe;
	return (open_redirections(new, pipeline, heredoc, core), new);
}

t_command	*form_command_list(t_pipeline *current, t_shell *core, t_heredoc *heredoc)
{
	t_command	*head;
	t_command	*current_command;
	int			index;

	head = NULL;
	index = 0;
	while (current)
	{
		if (!head)
		{
			head = form_command(current, index, core, heredoc);
			current_command = head;
		}
		else
		{
			current_command->next = form_command(current, index, core, heredoc);
			current_command = current_command->next;
		}
		if (!current_command)
			return (empty_command_list(head), NULL);
		index++;
		current = current->next;
	}
	return (head);
}

int	execute_tree(t_ast *tree, t_shell *core)
{
	int	ret;

	if (core->cur_process.error_index != DEFAULT || !tree)
		return (FAILURE);
	ret = execute_tree(tree->left, core);
	if (ret && tree->type == OR)
		return (execute_tree(tree->right, core));
	if (!ret && tree->type == AND)
		return (execute_tree(tree->right, core));
	if (tree->pipeline)
	{
		tree->command_list = form_command_list(tree->pipeline, core, tree->heredoc_list);
		if (tree->command_list)
		{
			tree->return_value = pipeline_execution(core, tree->command_list);
			tree->return_value = process_exit_status(tree->return_value, core);
			core->cur_process.ret = tree->return_value;
			if (core->cur_process.terminated)
				print_terminating_signal(core->cur_process.ret);
		}
	}
	if (tree->up)
		tree->up->return_value = tree->return_value;
	return (tree->return_value);
}