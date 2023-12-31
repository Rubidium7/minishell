/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_envs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvagapov <vvagapov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 13:58:56 by vvagapov          #+#    #+#             */
/*   Updated: 2023/09/18 13:56:55 by vvagapov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_bool	expand_words_envs(t_token *current, t_shell *core)
{
	char	*old_content;

	old_content = ft_strdup(current->content);
	if (!old_content)
		return (TRUE);
	current->content = expand_envs_in_string(current->content, core);
	if (!current->content)
		return (free(old_content), TRUE);
	if (!current->content[0] && old_content[0] && !current->quote)
		core->cur_process.empty_string = TRUE;
	if (current->after_redir && !current->content[0]
		&& old_content[0] && !current->quote)
	{
		current->ambiguity = TRUE;
		current->filename = old_content;
	}
	else
		free(old_content);
	return (FALSE);
}

t_bool	expand_envs(t_token *head, t_shell *core)
{
	t_token	*current;

	current = head;
	core->cur_process.empty_string = FALSE;
	while (current)
	{
		if (current->type == WORD 
			&& current->after_redir != HEREDOC && current->quote != 1)
		{
			if (expand_words_envs(current, core))
				return (TRUE);
		}
		current = current->next;
	}
	return (FALSE);
}
