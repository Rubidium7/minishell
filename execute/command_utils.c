/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvagapov <vvagapov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 22:28:56 by vvagapov          #+#    #+#             */
/*   Updated: 2023/09/18 14:10:30 by vvagapov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_first_command(t_command *command)
{
	return (!command->index);
}

int	is_last_command(t_command *command)
{
	return (!command->next);
}

int	has_args(char **args)
{
	int	i;

	i = 0;
	while (args[i])
		i++;
	if (i > 1)
		return (TRUE);
	return (FALSE);
}

t_bool	no_children_needed(t_command *commands)
{
	if (list_len(commands) > 1 || !commands->cmd_name)
		return (FALSE);
	if (!ft_strcmp(commands->cmd_name, "export") && has_args(commands->cmd_ar))
		return (TRUE);
	if (!ft_strcmp(commands->cmd_name, "cd")
		|| !ft_strcmp(commands->cmd_name, "exit")
		|| !ft_strcmp(commands->cmd_name, "unset"))
		return (TRUE);
	return (FALSE);
}
