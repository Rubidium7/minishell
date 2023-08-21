/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_and_words_syntax_rules.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlonka <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 18:41:53 by nlonka            #+#    #+#             */
/*   Updated: 2023/08/16 18:42:00 by nlonka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ast	*word_rule(t_token *current, t_ast *up, int end_index)
{
	t_ast	*words;
	t_ast	*left;
	t_ast	*right;

	if (!current)
		return (new_ast_node(up, NULL, NEW_LINE_ERROR));
	if (current->position > end_index)
		return (new_ast_node(up, current, WRONG_TOKEN_ERROR));
	words = new_ast_node(up, NULL, WORDS);
	if (!words)
		return (NULL);
	if (current->type == WORD)
		left = new_ast_node(words, current, WORD);
	else if (is_redir(current->type))
		left = redir_rule(words, current, )
	if (!current->next || current->position == end_index)
		return (words);
	if (is_redir(current->next->type))
}

t_ast	*pipe_rule(t_token *current, t_ast *up, int end_index)
{
	t_ast	*pipe;
	t_ast	*left;
	t_ast	*right;
	int		position;

	if (!current)
		return (new_ast_node(up, NULL, NEW_LINE_ERROR));
	if (current->position > end_index)
		return (new_ast_node(up, current, WRONG_TOKEN_ERROR));
	position = find_node(current, PIPE, end_index);
	if (!position)
		return (word_rule(current, up, end_index));
	pipe = new_ast_node(up, node_at_index(current, position), PIPE);
	if (!pipe)
		return (NULL);
	pipe->left = word_rule(current, pipe, position - 1);
	pipe->right = pipe_rule(node_at_index (current, position)->next, \
		pipe, end_index);
	return (pipe);
}