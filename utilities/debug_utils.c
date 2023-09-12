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

void	print_wildcard(t_wildcard *current)
{
	printf("-> has wildcard: ");
	while (current)
	{
		if (current->expand)
			printf("{%s}", current->str);
		else
			printf("%s", current->str);
		current = current->next;
	}
	printf("\n");
}

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
		if (current->wildcard)
			print_wildcard(current->wildcard);
		if (current->next)
			printf("   v   \n");
		current = current->next;
	}
}

void	print_token(t_token *token, int new_line)
{
	if (!token)
		printf("(null)");
	else if (token->type == HEAD)
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

void	print_pipeline_list(t_pipeline *pipeline)
{
	t_token	*current;

	if (!pipeline)
		return ;
	current = pipeline->start;
	while (current != pipeline->end)
	{
		print_token(current, OFF);
		if (current->next != pipeline->end)
			printf(" ");
		current = current->next;
	}
}

void	print_tree_in_execution_order(t_ast *tree)
{
	t_pipeline	*current;

	if (!tree)
		return ;
	if (tree->left)
		print_tree_in_execution_order(tree->left);
	if (tree->right)
		print_tree_in_execution_order(tree->right);
	current = tree->pipeline;
	while (current)
	{
		print_pipeline_list(current);
		if (current->next)
			printf(" | ");
		current = current->next;
		if (!current)
			printf("\n");
	}
}

void	print_file(const char *filename, int write_fd)
{
	size_t	read_characters;
	char	buffer[20];
	int		read_fd;

	read_characters = 1;
	read_fd = open(filename, O_RDONLY);
	while (read_fd != -1 && read_characters)
	{
		read_characters = read(read_fd, buffer, 20);
		buffer[read_characters] = '\0';
		//printf("read [%zu] characters\n", read_characters); //debug
		if (read_characters)
			write(write_fd, buffer, ft_strlen(buffer));
	}
	close(read_fd);
}

void	print_heredocs(t_ast *tree, int print_files)
{
	t_heredoc	*current;

	if (!tree)
		return ;
	print_heredocs(tree->left, print_files);
	print_heredocs(tree->right, print_files);
	if (tree->heredoc_list)
	{
		current = tree->heredoc_list;
		while (current)
		{
			printf("index is %d filename is [%s]\n", current->index, current->filename);
			if (print_files)
				print_file(current->filename, 1);
			current = current->next;
		}
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
