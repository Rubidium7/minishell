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

t_ast	*syntax_check(t_token *head, int *return_value)
{
	t_ast	*first_tree;
	//t_ast	*second_tree;
	int		first_error_index;
	//int		second_error_index;

	first_tree = pipe_rule(head, NULL, ft_lstsize((t_list *)head) - 1);
	first_error_index = check_tree(first_tree);
	if (!first_error_index)
		return (first_tree);
	syntax_error(UNEXPECTED_TOKEN, node_at_index(head, first_error_index));
	return (NULL);
	// second_tree = list_rule(head, NULL, ft_lstsize((t_list *)head) - 1);
	// second_error_index = check_tree(second_tree);
	// if (!second_error_index)
	// 	return (free_tree(first_tree), second_tree);
	// *return_value = 258;
	// if (first_error_index <= second_error_index)
	// 	syntax_error(UNEXPECTED_TOKEN, node_at_index(head, first_error_index));
	// else
	// 	syntax_error(UNEXPECTED_TOKEN, node_at_index(head, second_error_index));
	// return (free_tree(first_tree), free_tree(second_tree), NULL);
}
