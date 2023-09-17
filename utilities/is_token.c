

#include "minishell.h"


t_bool	is_redir(t_token_type type)
{
	if (type == RED_IN || type == HEREDOC)
		return (TRUE);
	if (type == RED_OUT || type == RED_OUT_APP)
		return (TRUE);
	return (FALSE);
}

t_bool	is_red_or_word(t_token_type type)
{
	if (type == WORD)
		return (TRUE);
	if (is_redir(type))
		return (TRUE);
	return (FALSE);
}
t_bool	is_ok_after_logic(t_token_type type)
{
	if (is_red_or_word(type))
		return (TRUE);
	if (type == LPAR)
		return (TRUE);
	return (FALSE);
}

t_bool	is_logic(t_token_type type)
{
	if (type == OR)
		return (TRUE);
	if (type == AND)
		return (TRUE);
	return (FALSE);
}