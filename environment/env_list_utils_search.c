/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list_utils_search.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvagapov <vvagapov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 20:19:05 by vvagapov          #+#    #+#             */
/*   Updated: 2023/09/18 14:31:55 by vvagapov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*find_env(t_env *env_list, const char *key)
{
	t_env	*curr_env;

	curr_env = env_list;
	while (curr_env && ft_strcmp(key, curr_env->key))
		curr_env = curr_env->next;
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
