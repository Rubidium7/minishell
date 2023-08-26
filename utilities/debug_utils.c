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

void	print_token_list(t_token *current, int print_quotes)
{
	while (current)
	{
		if (current->type == HEAD)
			printf("| HEAD |\n");
		if (current->type == WORD)
		{
			printf("| WORD | = '%s'", current->content);
			if (print_quotes == ON)
			{
				if (current->quote)
					printf(" quote = YES open_quote = ");
				else
					printf(" quote = NO open_quote = ");
				if (current->open_quote)
					printf("YES\n");
				else
					printf("NO\n");
			}
			else
				printf("\n");
		}
		if (current->type == RED_IN)
			printf("|  <   | = filename '%s'\n", current->filename);
		if (current->type == HEREDOC)
			printf("|  <<  | = filename '%s'\n", current->filename);
		if (current->type == RED_OUT)
			printf("|  >   | = filename '%s'\n", current->filename);
		if (current->type == RED_OUT_APP)
			printf("|  >>  | = filename '%s'\n", current->filename);
		if (current->type == PIPE)
			printf("|  |   |\n");
		if (current->type == OR)
			printf("|  ||  |\n");
		if (current->type == AMPERSAND)
			printf("|  &   |\n");
		if (current->type == AND)
			printf("|  &&  |\n");
		if (current->type == LPAR)
			printf("|  (   |\n");
		if (current->type == RPAR)
			printf("|  )   |\n");
		if (current->type == WHITESPACE)
			printf("|  WS  |\n");
		if (current->next)
			printf("   v   \n");
		current = current->next;
	}
}

void	print_token(t_token *token, int new_line)
{
	if (token->type == HEAD)
		printf("HEAD");
	else if (token->type == WORD)
		printf("'%s'", token->content);
	else if (token->type == RED_IN)
		printf("<");
	else if (token->type == HEREDOC)
		printf("<<");
	else if (token->type == RED_OUT)
		printf(">");
	else if (token->type == RED_OUT_APP)
		printf(">>");
	else if (token->type == PIPE)
		printf("|");
	else if (token->type == OR)
		printf("||");
	else if (token->type == AMPERSAND)
		printf("&");
	else if (token->type == AND)
		printf("&&");
	else if (token->type == LPAR)
		printf("(");
	else if (token->type == RPAR)
		printf(")");
	else if (token->type == WHITESPACE)
		printf("whitespace");
	else if (token->type == EMPTY)
		printf("(empty)");
	if (new_line)
		printf("\n");
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
