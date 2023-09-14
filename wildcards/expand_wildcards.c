/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_wildcards.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlonka <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 15:13:21 by nlonka            #+#    #+#             */
/*   Updated: 2023/09/14 15:13:23 by nlonka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_token	*new_list_member(t_token *head, char *file)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	if (!new)
		return (empty_token_list(head), NULL);
	zero_values(new);
	new->content = ft_strdup(file);
	if (!new->content)
		return (free(new), empty_token_list(head), NULL);
	new->type = WORD;
	if (!head)
		return (new);
	(last_token(head))->next = new;
	return (head);
}

t_token	*find_matches(t_wildcard *wildcard)
{
	t_token	*head;
	char	**files;
	int		i;

	files = ft_ls();
	if (!files)
		return (NULL);
	i = 0;
	head = NULL;
	while (files[i])
	{
		if (is_wildcard_match(files[i], wildcard))
		{
			head = new_list_member(head, files[i]);
			if (!head)
				return (error_print(WILDCARD_ERROR), free_ar(files), NULL);
		}
		i++;
	}
	free_ar(files);
	return (head);
}

static t_token	*add_to_list(t_token *freeable, t_token *head, t_token *found)
{
	t_token	*current;

	current = head;
	if (freeable == head)
	{
		last_token(found)->next = head->next;
		free_token_node(freeable);
		return (found);
	}
	while (current->next != freeable)
		current = current->next;
	last_token(found)->next = freeable->next;
	current->next = found;
	free_token_node(freeable);
	return (head);
}

t_token	*expand_wildcards(t_token *head)
{
	t_token	*current;
	t_token	*found;

	current = head;
	while (current)
	{
		if (current->wildcard && !current->after_redir)
		{
			found = find_matches(current->wildcard);
			if (found)
				head = add_to_list(current, head, found);
		}
		current = current->next;
	}
	return (head);
}
