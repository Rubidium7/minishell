/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvagapov <vvagapov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 21:26:23 by vvagapov          #+#    #+#             */
/*   Updated: 2023/09/18 18:42:51 by vvagapov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	export(t_shell *core, t_command *command)
{
	int	i;
	int	first_error_ret;
	int	ret;


	i = 1;
	first_error_ret = 0;
	while (command->cmd_ar[i])
	{
		ret = add_env_from_string(core, command->cmd_ar[i]);
		if (ret && !first_error_ret)
			first_error_ret = ret;
		i++;
	}
	if (i == 1)
		print_envs(EXPORT, core);
	return (first_error_ret);
}
