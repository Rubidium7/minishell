/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvagapov <vvagapov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 21:26:36 by vvagapov          #+#    #+#             */
/*   Updated: 2023/09/19 08:33:56 by vvagapov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_bool	is_valid_key(const char *key)
{
	int	i;

	if (!is_env_first_char(key[0]))
		return (FALSE);
	i = 1;
	while (key[i])
	{
		if (!is_env_char(key[i]))
			return (FALSE);
		i++;
	}
	return (TRUE);
}

int	unset(t_shell *core, t_command *command)
{
	int	i;
	int	ret;

	i = 1;
	ret = 0;
	while (command->cmd_ar[i])
	{
		if (!is_valid_key(command->cmd_ar[i]))
		{
			print_generic_error("unset", command->cmd_ar[i],
				"not a valid identifier");
			ret = 1;
		}
		else
			unset_env(command->cmd_ar[i], core);
		i++;
	}
	return (ret);
}
