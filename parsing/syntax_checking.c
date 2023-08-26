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

t_ast	*syntax_check(t_token *head, t_shell *core)
{
	//t_ast		*tree;
	t_pipeline	*pipeline;
	int			index;

	core->cur_process.error_index = DEFAULT;
	index = find_logic_token(head);
	if (index == -1)
	{
		pipeline = form_pipeline(head, INT_MAX, &core->cur_process.error_index);
		if (!pipeline)
		{
			if (core->cur_process.error_index == MALLOC_FAIL)
				return (error_print(PARSE_ERROR), NULL);
			if (core->cur_process.error_index == UNEXPECTED_NL)
				return (syntax_error(UNEXPECTED_NL, NULL), NULL);
			return (syntax_error(UNEXPECTED_TOKEN, \
			node_at_index(head, core->cur_process.error_index)), NULL);
		}
		return (new_ast_node(NULL, pipeline, PIPELINE));
	}
	return (NULL);
}
