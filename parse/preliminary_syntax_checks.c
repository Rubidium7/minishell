/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preliminary_syntax_checks.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvagapov <vvagapov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 16:34:28 by vvagapov          #+#    #+#             */
/*   Updated: 2023/09/18 16:34:33 by vvagapov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_bool	is_next_token_ok(t_token *current, t_token *next)
{
// 	printf("comparing: ");
// 	print_token(current, OFF);
// 	printf(" and ");
// 	print_token(next, OFF);
// 	printf("\n");
	if (current->type == WORD && next->type == LPAR)
		return (FALSE);
	if (current->type == PIPE && !is_red_or_word(next->type))
		return (FALSE);
	if (is_logic(current->type)
		&& next->type != LPAR && !is_red_or_word(next->type))
		return (FALSE);
	if (current->type == LPAR && !is_red_or_word(next->type))
		return (FALSE);
	if (current->type == RPAR && !is_logic(next->type))
		return (FALSE);
	return (TRUE);
}

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
		if (current->next && !is_next_token_ok(current, current->next))
			return (handle_error_value(error_index, current->next->position), TRUE);
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
		if (amount < 0)
			return (handle_error_value(error_index, current->position), TRUE);
		current = current->next;
	}
	if (amount > 0)
		return (handle_error_value(error_index, UNEXPECTED_NL), TRUE);
	return (FALSE);
}

void	preliminary_syntax_check(t_shell *core)
{
	open_parentheses(core->tokens, &core->cur_process.error_index);
	separated_syntax_check(core->tokens, &core->cur_process.error_index);
}