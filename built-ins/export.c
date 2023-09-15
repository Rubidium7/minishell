/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvagapov <vvagapov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 21:26:23 by vvagapov          #+#    #+#             */
/*   Updated: 2023/09/15 19:31:12 by vvagapov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	export(t_shell *core, t_command *command)
{
	int		i;

	i = 1;
	while (command->cmd_ar[i])
	{
		if (add_env_from_string(core, command->cmd_ar[i]))
			return (1);
		i++;
	}
	if (i == 1)
		print_envs(EXPORT, core);
	return (0);
}
