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

t_ast	*word_rule(t_token *section, t_ast *up, int end_index)
{
	t_ast	*words;
	t_ast	*left;
	t_ast	*right;

	if (!section || section->position > end_index)
		return (new_ast_node(up, NULL, NEW_LINE_ERROR));
	words = new_ast_node(up, NULL, WORDS);
	if (!words)
		return (NULL);
	if (section->type == WORD)
		left = new_ast_node(words, section, WORD);
	else if (is_redir(redir))
		
	if (!section->next || section->position == end_index)
		return (words);
	if (is_redir(section->next->type))
}

t_ast	*pipe_rule(t_token *section, t_ast *up, int end_index)
{
	t_ast	*pipe;
	t_ast	*left;
	t_ast	*right;
	int		position;

	if (!section || section->position > end_index)
		return (new_ast_node(up, NULL, NEW_LINE_ERROR));
	position = find_node(section, PIPE, end_index);
	if (!position)
		return (word_rule(section, up, end_index));
	pipe = new_ast_node(up, node_at_index(section, position), PIPE);
	if (!pipe)
		return (NULL);
	pipe->left = word_rule(section, pipe, position - 1);
	pipe->right = pipe_rule(node_at_index (section, position)->next, \
		pipe, end_index);
	return (pipe);
}