/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaners.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlonka <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 17:13:27 by nlonka            #+#    #+#             */
/*   Updated: 2023/08/15 18:55:57 by nlonka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	empty_token_list(t_token *current)
{
	t_token	*prev;

	while (current)
	{
		prev = current;
		if (current->content)
			free(current->content);
		current = current->next;
		free(prev);
	}
}
