/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvagapov <vvagapov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 20:19:05 by vvagapov          #+#    #+#             */
/*   Updated: 2023/09/15 14:47:51 by vvagapov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*find_env(t_env *env_list, const char *key)
{
	t_env	*curr_env;

	curr_env = env_list;
	while (curr_env && ft_strcmp(key, curr_env->key))
	{
		curr_env = curr_env->next;
	}
	return (curr_env);
}

// RETURNS:
// - pointer to a node before matching variable if the match is found
// - NULL if the matching node is first
// - pointer to the last node if no match is found
t_env	*find_prev(t_env *env_list, const char *key)
{
	t_env	*curr_env;
	t_env	*prev;

	curr_env = env_list;
	prev = NULL;
	while (curr_env && ft_strcmp(key, curr_env->key))
	{
		prev = curr_env;
		curr_env = curr_env->next;
	}
	return (prev);
}

// RETURNS:
// - TRUE if there's not next element
// - FALSE if the next node was successfully removed
t_bool	delete_next(t_env *env_list)
{
	t_env	*new_next;

	if (!env_list->next)
		return (TRUE);
	new_next = env_list->next->next;
	free(env_list->next);
	env_list->next = new_next;
	return (FALSE);
}

// RETURNS:
// - TRUE if there's not next element
// - FALSE if the next node was successfully removed
t_env	*delete_first(t_env *env_list)
{
	t_env	*res;

	if (!env_list)
		return (NULL);
	res = env_list->next;
	free(env_list);
	return (res);
}

t_env	*create_env_var(const char *key, const char *content)
{
	t_env	*res;

	res = malloc(sizeof(t_env));
	if (res)
	{
		res->key = ft_strdup(key);
		res->content = ft_strdup(content);
		if (!res->key || (content && !res->content))
			return (NULL);
		res->next = NULL;
	}
	return (res);
}

t_env	*add_node_to_end(t_env *env_list, t_env *new_node)
{
	t_env	*tmp;
	
	if(!env_list)
	{
		return (new_node);
	}
	tmp = env_list;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_node;
	return (env_list);
}

void	clear_env_list(t_env *env_list)
{
	while (env_list)
		env_list = delete_first(env_list);
}
