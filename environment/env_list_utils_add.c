/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list_utils_add.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvagapov <vvagapov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 20:19:05 by vvagapov          #+#    #+#             */
/*   Updated: 2023/09/18 20:31:51 by vvagapov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

	if (!env_list)
		return (new_node);
	tmp = env_list;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_node;
	return (env_list);
}
