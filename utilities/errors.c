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
