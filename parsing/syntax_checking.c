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
	t_ast		*tree;
	t_pipeline	*pipeline;
	int			index;

	core->cur_process.error_index = -1;
	index = find_logic_token(head);
	if (index == -1)
	{
		pipeline = form_pipeline(head, \
		ft_lstsize((t_list *)head) + 1, &core->cur_process.error_index);
		if (!pipeline)
		{
			if (core->cur_process.error_index == -2)
				return (error_print(PARSE_ERROR), NULL);
			return (syntax_error(UNEXPECTED_TOKEN, \
			node_at_index(head, core->cur_process.error_index)));
		}
		return (new_ast_node(NULL, pipeline, PIPELINE));
	}
	return (NULL);
}
