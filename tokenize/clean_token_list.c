/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_token_list.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlonka <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 19:15:39 by nlonka            #+#    #+#             */
/*   Updated: 2023/08/15 20:02:40 by nlonka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_bool	is_empty(t_token *token)
{
	if (token && token->type == WORD)
	{
		if (!token->quote)
		{
			if (!token->content || !token->content[0])
				return (TRUE);
		}
	}
	return (FALSE);
}

t_token	*cleap_empty_strings(t_token *head)
{
	t_token	*current;
	t_token	*tmp;

	if (is_empty(head))
	{
		tmp = head;
		head = head->next;
		free(tmp);
	}
	current = head;
	while (current)
	{
		if (is_empty(current->next))
		{
			tmp = current->next;
			current->next = current->next->next;
			free(tmp);
		}
		current = current->next;
	}
	return (head);
}

t_token	*clean_whitespace(t_token *head)
{
	t_token	*current;
	t_token	*tmp;

	if (head && head->type == WHITESPACE)
	{
		tmp = head;
		head = head->next;
		free(tmp);
	}
	current = head;
	while (current)
	{
		if (current->next && current->next->type == WHITESPACE)
		{
			tmp = current->next;
			current->next = current->next->next;
			free(tmp);
		}
		current = current->next;
	}
	return (cleap_empty_strings(head));
}

void	add_up_values(t_token *current, t_token *next)
{
	if (current->quote || next->quote)
		current->quote = 1;
	if (current->open_quote || next->open_quote)
		current->open_quote = TRUE;
	if (current->ambiguity || next->ambiguity)
		current->ambiguity = TRUE;
}

t_token	*clean_quotes_and_whitespaces(t_token *head, t_token *current)
{
	t_token	*tmp;
	char	*str;

	current = head;
	while (current)
	{
		if (current->type == WORD && current->next && current->next->type == WORD)
			{
				str = ft_strjoin(current->content, current->next->content);
				if (!str)
					return (NULL);
				free(current->content);
				free(current->next->content);
				add_up_values(current, current->next);
				current->content = str;
				tmp = current->next;
				current->next = current->next->next;
				free(tmp);
			}
		else
			current = current->next;
	}
	return (clean_whitespace(head));
}
