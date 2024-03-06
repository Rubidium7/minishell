/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error_printing.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvagapov <vvagapov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 17:56:49 by vvagapov          #+#    #+#             */
/*   Updated: 2023/09/19 08:24:16 by vvagapov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_error_token(t_token *token)
{
	if (!token)
		;
	else if (token->type == WORD)
		ft_putstr_fd(token->content, STDERR_FILENO);
	else if (token->type == RED_IN)
		ft_putstr_fd("<", STDERR_FILENO);
	else if (token->type == HEREDOC)
		ft_putstr_fd("<<", STDERR_FILENO);
	else if (token->type == RED_OUT)
		ft_putstr_fd(">", STDERR_FILENO);
	else if (token->type == RED_OUT_APP)
		ft_putstr_fd(">>", STDERR_FILENO);
	else if (token->type == PIPE)
		ft_putstr_fd("|", STDERR_FILENO);
	else if (token->type == OR)
		ft_putstr_fd("||", STDERR_FILENO);
	else if (token->type == AMPERSAND)
		ft_putstr_fd("&", STDERR_FILENO);
	else if (token->type == AND)
		ft_putstr_fd("&&", STDERR_FILENO);
	else if (token->type == LPAR)
		ft_putstr_fd("(", STDERR_FILENO);
	else if (token->type == RPAR)
		ft_putstr_fd(")", STDERR_FILENO);
}

t_bool	syntax_error(t_syntax_error type, t_token *token)
{
	ft_putstr_fd(ERROR_SHROOM, STDERR_FILENO);
	if (type == OPEN_QUOTE)
	{
		ft_putendl_fd("syntax error unclosed quotes", STDERR_FILENO);
		return (TRUE);
	}
	if (type == OPEN_PARENTHESES)
	{
		ft_putendl_fd("syntax error unclosed parentheses", STDERR_FILENO);
		return (TRUE);
	}
	ft_putstr_fd("syntax error near unexpected token `", STDERR_FILENO);
	if (type != UNEXPECTED_NL && token)
		print_error_token(token);
	else
		ft_putstr_fd("newline", STDERR_FILENO);
	ft_putstr_fd("'\n", STDERR_FILENO);
	return (TRUE);
}
