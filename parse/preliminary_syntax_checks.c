
#include "minishell.h"

t_bool	check_redirection_syntax(t_token *current)
{
	while (current)
	{
		if (is_redir(current->type))
		{
			if (!current->next)
				return (syntax_error(UNEXPECTED_NL, NULL));
			if (current->next->type != WORD)
				return (syntax_error(UNEXPECTED_TOKEN, current->next));				
		}
		current = current->next;
	}
	return (FALSE);
}

t_bool	open_quotes(t_token *current)
{
	while (current)
	{
		if (current->open_quote)
			return (syntax_error(OPEN_QUOTE, NULL));
		current = current->next;
	}
	return (FALSE);
}

t_bool	open_parentheses(t_token *current)
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
		return (syntax_error(OPEN_PARENTHESES, NULL));
	return (FALSE);
}

t_bool	preliminary_syntax_check(t_shell *core)
{
	if (open_quotes(core->tokens) || open_parentheses(core->tokens) 
		|| check_redirection_syntax(core->tokens)) //add check ampersand
	{
		core->cur_process.ret = SYNTAX_ERROR;
		return (TRUE);
	}
	return (FALSE);
}