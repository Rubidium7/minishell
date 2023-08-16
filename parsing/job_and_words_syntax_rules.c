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

t_ast	*word_rule(t_token *current, t_ast *up)
{

	
}

t_ast	*job_rule(t_token *head, t_ast *up)
{
	t_ast	*job;
	t_token	*current;

	if (!head)
		return (new_ast_node(up, NULL, NEW_LINE_ERROR, EMPTY));
	current = head;
	job = new_ast_node(up, NULL, JOB, EMPTY);
	if (!job)
		return (NULL); ////figure out how to catch these
	job->right = word_rule(current, job);
	current = find_last_node(job->right);
	if (!current->next)
		return (job);
	else if (current->next->type == PIPE)
	{
		job->left = new_ast_node(job, current->next, TERMINAL, EMPTY);
		if (!job->left)
			return (NULL);
		job->left->left = job_rule(current->next->next, job);
	}
}