
#include "minishell.h"

t_bool	separated_syntax_check(t_token *current, int *error_index)
{
	while (current)
	{
		if (is_redir(current->type))
		{
			if (!current->next)
				return (handle_error_value(error_index, UNEXPECTED_NL), TRUE);
			if (current->next->type != WORD)
				return (handle_error_value(error_index, current->next->position), TRUE);
		}
		if (current->open_quote)
			return (handle_error_value(error_index, UNEXPECTED_NL), TRUE);
		if (current->type == AMPERSAND)
				return (handle_error_value(error_index, current->position), TRUE);
		current = current->next;
	}
	return (FALSE);
}

t_bool	open_parentheses(t_token *current, int *error_index)
{
	int	amount;

	amount = 0;
	while (current)
	{
		if (current->type == LPAR)
			amount++;
		if (current->type == RPAR)
			amount--;
		current = current->next;
	}
	if (amount > 0)
		return (handle_error_value(error_index, UNEXPECTED_NL), TRUE);
	return (FALSE);
}

t_bool	preliminary_syntax_check(t_shell *core)
{
	if (open_parentheses(core->tokens, &core->cur_process.error_index)
	|| separated_syntax_check(core->tokens, &core->cur_process.error_index))
	{
		
		core->cur_process.ret = SYNTAX_ERROR;
		return (TRUE);
	}
	return (FALSE);
}