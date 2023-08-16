/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_checking.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlonka <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 14:18:42 by nlonka            #+#    #+#             */
/*   Updated: 2023/08/16 14:42:54 by nlonka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_bool	open_quotes(t_token *current)
{
	while (current)
	{
		if (current->open_quote)
			return (TRUE);
		current = current->next;
	}
	return (FALSE);
}

t_bool	syntax_check(t_token *head)
{
	t_ast	*tree_head;

	if (open_quotes(head))
		return (syntax_error(OPEN_QUOTE, NULL));
	if (open_parentheses(head))
		return (syntax_error(OPEN_PARENTHESES, NULL));
	tree_head = job_rule(head, NULL);
	if (tree_head)
		return (FALSE);
	tree_head = list_rule(head, NULL);
	if (tree_head)
		return (FALSE);
	else
		return (TRUE);
}
