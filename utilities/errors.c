/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlonka <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 17:06:16 by nlonka            #+#    #+#             */
/*   Updated: 2023/08/16 14:41:36 by nlonka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_error_value(int *error_index, int position)
{
	//printf("1 error position is %d\n", position); //debug
	if (*error_index == DEFAULT)
		*error_index = position;
	else if (position != UNEXPECTED_NL && position < *error_index)
		*error_index = position;
	//printf("2 error position is %d\n", *error_index); //debug
}

void	update_error_value(t_shell *core)
{
	int	error;

	error = core->cur_process.error_index;
	if (error == MALLOC_FAIL)
		core->cur_process.ret = MALLOC_ERROR;
	else if (error == OPEN_ERROR)
		core->cur_process.ret = OPEN_ERROR;
	else if (error != DEFAULT && !core->cur_process.ret)
		core->cur_process.ret = SYNTAX_ERROR;
}

void	error_print(t_error_code type)
{
	if (type == SETUP_ERROR)
		ft_putendl_fd("ERROR in setting up process🕷🕸", 2);
	if (type == TOKEN_ERROR)
		ft_putendl_fd("ERROR in tokenizing process🕷🕸", 2);
	if (type == PARSE_ERROR)
		ft_putendl_fd("ERROR in parsing process🕷🕸", 2);
}

void	print_error_token(t_token *token)
{
	if (token->type == WORD)
		ft_putstr_fd(token->content, 2);
	else if (token->type == RED_IN)
		ft_putstr_fd("<", 2);
	else if (token->type == HEREDOC)
		ft_putstr_fd("<<", 2);
	else if (token->type == RED_OUT)
		ft_putstr_fd(">", 2);
	else if (token->type == RED_OUT_APP)
		ft_putstr_fd(">>", 2);
	else if (token->type == PIPE)
		ft_putstr_fd("|", 2);
	else if (token->type == OR)
		ft_putstr_fd("||", 2);
	else if (token->type == AMPERSAND)
		ft_putstr_fd("&", 2);
	else if (token->type == AND)
		ft_putstr_fd("&&", 2);
	else if (token->type == LPAR)
		ft_putstr_fd("(", 2);
	else if (token->type == RPAR)
		ft_putstr_fd(")", 2);
}

void	print_file_error(char *filename, t_error_code type)
{
	ft_putstr_fd(ERROR_SHROOM, 2);
	if (type != HEREDOC_FILE_ERROR)
		ft_putstr_fd(filename, 2);
	if (type == NO_RIGHTS)
		ft_putendl_fd(": Permission denied", 2);
	if (type == NO_FILE)
		ft_putendl_fd(": No such file or directory", 2);
}

t_bool	syntax_error(t_syntax_error type, t_token *token)
{
	ft_putstr_fd(ERROR_SHROOM, 2);
	if (type == OPEN_QUOTE)
	{
		ft_putendl_fd("syntax error unclosed quotes", 2);
		return (TRUE);
	}
	if (type == OPEN_PARENTHESES)
	{
		ft_putendl_fd("syntax error unclosed parentheses", 2);
		return (TRUE);
	}
	ft_putstr_fd("syntax error near unexpected token `", 2);
	if (type != UNEXPECTED_NL && token->new_line_error == FALSE)
		print_error_token(token);
	else
		ft_putstr_fd("newline", 2);
	ft_putstr_fd("'\n", 2);
	return (TRUE);
}
