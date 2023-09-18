/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_wildcards.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvagapov <vvagapov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 15:13:48 by nlonka            #+#    #+#             */
/*   Updated: 2023/09/17 23:38:37 by vvagapov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_bool	has_wildcard(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		if (str[i] == '*')
			return (TRUE);
		i++;
	}
	return (FALSE);
}

t_token	*clean_non_wildcards(t_token *head, t_token *current)
{
	t_wildcard	*current_wild;
	t_bool		has_expand;

	while (current)
	{
		if (current->wildcard)
		{
			has_expand = FALSE;
			current_wild = current->wildcard;
			while (current_wild)
			{
				if (current_wild->expand)
					has_expand = TRUE;
				current_wild = current_wild->next;
			}
			if (!has_expand)
			{
				empty_wildcard_list(current->wildcard);
				current->wildcard = NULL;
			}
		}
		current = current->next;
	}
	return (head);
}

static t_wildcard	*new_wildcard(t_token *token)
{
	t_wildcard	*new;

	new = malloc(sizeof(t_wildcard));
	if (!new)
		return (error_print(WILDCARD_ERROR), NULL);
	if (token->quote || !has_wildcard(token->content))
		new->expand = FALSE;
	else
		new->expand = TRUE;
	new->next = NULL;
	new->str = ft_strdup(token->content);
	if (!new->str)
		return (free(new), NULL);
	return (new);
}

static t_wildcard	*add_wildcard(t_token *list_safe, t_token *current)
{
	t_wildcard	*new;
	t_wildcard	*current_wild;

	new = new_wildcard(current);
	if (!new)
		return (empty_wildcard_list(list_safe->wildcard), NULL);
	if (!list_safe->wildcard)
		list_safe->wildcard = new;
	else
	{
		current_wild = list_safe->wildcard;
		while (current_wild->next)
			current_wild = current_wild->next;
		current_wild->next = new;
	}
	return (list_safe->wildcard);
}

void	save_wildcards(t_token *current)
{
	t_token_type	prev_type;
	t_token			*list_safe;

	prev_type = HEAD;
	while (current)
	{
		if (current->type == WORD && prev_type != WORD)
			list_safe = current;
		if (current->type == WORD)
		{
			list_safe->wildcard = add_wildcard(list_safe, current);
			if (!list_safe->wildcard)
				return ;
		}
		prev_type = current->type;
		current = current->next;
	}
}
