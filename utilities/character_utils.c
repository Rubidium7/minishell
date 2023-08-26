/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   character_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlonka <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 18:34:25 by nlonka            #+#    #+#             */
/*   Updated: 2023/08/15 19:00:01 by nlonka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_bool	is_whitespace(char c)
{
	if (c == ' ')
		return (TRUE);
	if (c >= 9 && c <= 13)
		return (TRUE);
	return (FALSE);
}

t_bool	is_special_char(char c)
{
	if (c == '<' || c == '>')
		return (TRUE);
	if (c == '|' || c == '&')
		return (TRUE);
	if (c == '(' || c == ')')
		return (TRUE);
	if (c == '\'' || c == '\"')
		return (TRUE);
	return (FALSE);
}

t_bool	is_redir(t_token_type type)
{
	if (type == RED_IN || type == HEREDOC)
		return (TRUE);
	if (type == RED_OUT || type == RED_OUT_APP)
		return (TRUE);
	return (FALSE);
}