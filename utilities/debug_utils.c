/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlonka <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 18:45:14 by nlonka            #+#    #+#             */
/*   Updated: 2023/08/15 19:13:01 by nlonka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_token_list(t_token *current)
{
	while (current)
	{
		if (current->type == HEAD)
			printf("| HEAD |\n");
		if (current->type == WORD)
			printf("| WORD | = '%s'\n", current->content);
		if (current->type == RED_IN)
			printf("|  <  |\n");
		if (current->type == HEREDOC)
			printf("|  <<  |\n");
		if (current->type == RED_OUT)
			printf("|  >  |\n");
		if (current->type == RED_OUT_APP)
			printf("|  >>  |\n");
		if (current->type == PIPE)
			printf("|  |  |\n");
		if (current->type == OR)
			printf("|  ||  |\n");
		if (current->type == AMPERSAND)
			printf("|  &  |\n");
		if (current->type == AND)
			printf("|  &&  |\n");
		if (current->type == LPAR)
			printf("|  (  |\n");
		if (current->type == RPAR)
			printf("|  )  |\n");
		if (current->type == WHITESPACE)
			printf("|  WS  |\n");
		if (current->next)
			printf("   v   \n");
		current = current->next;
	}
}

void	print_ar(char **array)
{
	int i = 0;

	while (array[i])
	{
		printf("%s\n", array[i]);
		i++;
	}
}