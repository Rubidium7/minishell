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

void	empty_command_list(t_command *current)
{
	t_command	*prev;

	while (current)
	{
		if (current->cmd_name)
			free(current->cmd_name);
		if (current->cmd_ar)
			free_ar(current->cmd_ar);
		prev = current;
		current = current->next;
		free(prev);
	}
}

void	empty_list(t_list *current)
{
	t_list	*prev;

	while (current)
	{
		prev = current;
		current = current->next;
		free(prev);
	}
}

void	clean_up(t_shell *core)
{
	empty_token_list(core->tokens);
}