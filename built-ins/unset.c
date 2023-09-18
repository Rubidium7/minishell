/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvagapov <vvagapov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 21:26:36 by vvagapov          #+#    #+#             */
/*   Updated: 2023/09/18 19:16:12 by vvagapov         ###   ########.fr       */
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
			core->cur_process.error_index = INVALID_IDENTIFIER;
			ft_putstr_fd(ERROR_SHROOM, 2);
			ft_putstr_fd(" unset: `", 2);
			ft_putstr_fd(command->cmd_ar[i], 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			ret = 1;
		}
		else if (unset_env(command->cmd_ar[i], core) && !ret)
			ret = 1;
		i++;
	}
	return (ret);
}
