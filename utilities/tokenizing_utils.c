/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizing_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlonka <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 18:34:19 by nlonka            #+#    #+#             */
/*   Updated: 2023/09/14 15:17:32 by nlonka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_quoted_word(char *str, size_t *i, int quote, t_token *new)
{
	size_t	size;
	char	*word;

	size = 0;
	*i += 1;
	while (str[*i + size] && ((str[*i + size] != '\'' && quote == 1)
	|| (str[*i + size] != '\"' && quote == 2)))
		size++;
	if (!str[*i + size])
		new->open_quote = TRUE;
	word = malloc(sizeof(char) * (size + 1));
	if (!word)
		return (NULL);
	word[size] = '\0';
	size = 0;
	while (str[*i] && ((str[*i] != '\'' && quote == 1)
	|| (str[*i] != '\"' && quote == 2)))
	{
		word[size] = str[*i];
		size++; //so sorry for using the size var for an index here 😭
		*i += 1;
	}
	if (new->open_quote == FALSE)
		*i += 1;
	return (word);
}

char	*get_word_token(char *str, size_t *i)
{
	size_t	size;
	char	*word;
	size_t	word_ind;

	size = 0;
	word_ind = 0;
	while (str[*i + size] && !is_special_char(str[*i + size])
	&& !is_whitespace(str[*i + size]))
		size++;
	word = malloc(sizeof(char) * (size + 1));
	if (!word)
		return (NULL);
	word[size] = '\0';
	while (str[*i] && !is_special_char(str[*i]) && !is_whitespace(str[*i]))
	{
		word[word_ind] = str[*i];
		*i += 1;
		word_ind++;
	}
	return (word);
}

void	carve_out_whitespace(char *str, size_t *i)
{
	while (str[*i] && is_whitespace(str[*i]))
		*i += 1;
}

size_t	size_of_token(t_token_type type)
{
	if (type == WORD || type == WHITESPACE)
		return (0);
	else if (type == HEREDOC || type == RED_OUT_APP)
		return (2);
	else if (is_logic(type))
		return (2);
	else
		return (1);
}

void	indexify_token_list(t_token *current)
{
	int		i;
	t_bool	is_prev_redir;

	i = 0;
	is_prev_redir = FALSE;
	while (current)
	{
		if (is_prev_redir && current->type == WORD)
		{
			current = current->next;
			is_prev_redir = FALSE;
			continue ;
		}
		current->position = i;
		i++;
		if (is_redir(current->type))
			is_prev_redir = TRUE;
		current = current->next;
	}
}

