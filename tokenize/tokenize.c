/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlonka <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 11:03:56 by nlonka            #+#    #+#             */
/*   Updated: 2023/08/16 14:17:56 by nlonka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	zero_values(t_token *new)
{
	new->content = NULL;
	new->filename = NULL;
	new->next = NULL;
	new->quote = 0;
	new->open_quote = FALSE;
	new->after_redir = HEAD;
	new->ambiguity = FALSE;
}

t_token	*new_token(t_token_type type, char *str, size_t *i)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	zero_values(new);
	new->type = type;
	if (type == WORD)
	{
		if (str[*i] == '\'')
			new->quote = 1;
		else if (str[*i] == '\"')
			new->quote = 2;
		if (new->quote)
			new->content = get_quoted_word(str, i, new->quote, new);
		else
			new->content = get_word_token(str, i);
		if (!new->content)
			return (NULL);
	}
	return (new);
}

t_token_type	identify_token(char *str, size_t i)
{
	if (str[i] == '<' && str[i + 1] == '<')
		return (HEREDOC);
	else if (str[i] == '<')
		return (RED_IN);
	else if (str[i] == '>' && str[i + 1] == '>')
		return (RED_OUT_APP);
	else if (str[i] == '>')
		return (RED_OUT);
	else if (str[i] == '|' && str[i + 1] == '|')
		return (OR);
	else if (str[i] == '|')
		return (PIPE);
	else if (str[i] == '&' && str[i + 1] == '&')
		return (AND);
	else if (str[i] == '&')
		return (AMPERSAND);
	else if (str[i] == '(')
		return (LPAR);
	else if (str[i] == ')')
		return (RPAR);
	else if (is_whitespace(str[i]))
		return (WHITESPACE);
	else
		return (WORD);
}

t_token	*tokenize(char *str, t_shell *core)
{
	size_t			i;
	t_token_type	type;
	t_token			*head;
	t_token			*current;

	i = 0;
	head = new_token(HEAD, NULL, &i);
	if (!head)
		return (NULL);
	current = head;
	while (str[i])
	{
		type = identify_token(str, i);
		i += size_of_token(type);
		current->next = new_token(type, str, &i);
		if (!current->next)
			return (empty_token_list(head), NULL);
		current = current->next;
		if (type == WHITESPACE)
			carve_out_whitespace(str, &i);
	}
	////expand envss HERE, don't expand if after heredoc :D
	mark_redirections(head);
	if (expand_envs(head, core))
			return (empty_token_list(head), NULL);
	return (clean_quotes_and_whitespaces(head, head));
}
