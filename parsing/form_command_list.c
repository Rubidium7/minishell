
#include "minishell.h"


// int	count_words(t_token *current, t_token *end)
// {
// 	int	amount;

// 	amount = 0;
// 	while (current != end)
// 	{
// 		if (current->type == WORD)
// 			amount++;
// 	}
// 	return (amount);
// }

// t_bool	fill_command_array(char **array, t_token *current, t_token *end)
// {
// 	int	index;

// 	index = 0;
// 	while (current != end)
// 	{
// 		if (current->type == WORD)
// 		{
// 			array[index] = ft_strdup(current->content);
// 			if (!array[index])
// 				return (TRUE);
// 			index++;
// 		}
// 		current = current->next;
// 	}
// 	array[index] = NULL;
// 	return (FALSE);
// }

// t_command	*form_command_node(t_command *head_command, \
// 			t_token *end_token, t_token *head_token, int *error_index)
// {
// 	t_command	*new;
// 	t_token		*current_token;
// 	int			size;

// 	current_token = head_token;
// 	if (incorrect_token_in_pipeline(current_token, end_token, error_index))
// 		return (head_command);
// 	size = count_words(current_token, end_token);
//	new = malloc(sizeof(t_command));
// 	new->cmd_ar = malloc(sizeof(char *) * (size + 1));
// 	if (!new->cmd_ar || !fill_command_array(new->cmd_ar, current_token, end_token))
// 	{
// 		*error_index = -2;
// 		return (head_command);
// 	}
// 	new->cmd_name = new->cmd_ar[0];
// }
