/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvagapov <vvagapov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 21:26:36 by vvagapov          #+#    #+#             */
/*   Updated: 2023/09/15 19:35:05 by vvagapov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	unset(t_shell *core, t_command *command)
{
	int	i;

	i = 1;
	while (command->cmd_ar[i])
	{
		if (unset_env(command->cmd_ar[i], core))
			return (1);
		i++;
	}
	return (0);
}
