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

int	is_whitespace(char c)
{
	if (c == ' ')
		return (1);
	if (c >= 9 && c <= 13)
		return (1);
	return (0);
}

int is_special_char(char c)
{
	if (c == '<' || c == '>')
		return (1);
	if (c == '|' || c == '&')
		return (1);
	if (c == '(' || c == ')')
		return (1);
	if (c == '\'' || c == '\"')
		return (1);
	return (0);
}
