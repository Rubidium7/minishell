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

t_token	*clean_whitespace(t_token *head)
{
	t_token	*current;
	t_token	*tmp;

	if (head->type == WHITESPACE)
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
	return (head);
}

void	add_up_quotes(int *cur_quote, t_bool *open_quote,\
int next_quote, t_bool next_open_quote)
{
	if (*cur_quote || next_quote)
		*cur_quote = 1;
	if (*open_quote || next_open_quote)
		*open_quote = TRUE;
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
				add_up_quotes(&current->quote, &current->open_quote,\
				current->next->quote, current->next->open_quote);
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
