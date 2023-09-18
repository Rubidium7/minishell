/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list_utils_delete.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvagapov <vvagapov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 20:19:05 by vvagapov          #+#    #+#             */
/*   Updated: 2023/09/18 23:10:38 by vvagapov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// RETURNS:
// - TRUE if there's not next element
// - FALSE if the next node was successfully removed
t_bool	delete_next(t_env *env_list)
{
	t_env	*new_next;

	if (!env_list->next)
		return (TRUE);
	new_next = env_list->next->next;
	if (env_list->next->key)
		free(env_list->next->key);
	if (env_list->next->content)
		free(env_list->next->content);
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
	if (env_list->key)
		free(env_list->key);
	if (env_list->content)
		free(env_list->content);
	free(env_list);
	return (res);
}

void	clear_env_list(t_env *env_list)
{
	while (env_list)
		env_list = delete_first(env_list);
}
