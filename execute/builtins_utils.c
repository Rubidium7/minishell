/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvagapov <vvagapov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 12:18:59 by vvagapov          #+#    #+#             */
/*   Updated: 2023/09/18 12:20:08 by vvagapov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	run_builtin(t_shell *core, t_command *command)
{
	if (!ft_strcmp(command->cmd_name, "pwd"))
		return (pwd(core));
	else if (!ft_strcmp(command->cmd_name, "exit"))
		return (ft_exit(core, command));
	else if (!ft_strcmp(command->cmd_name, "echo"))
		return (echo(command));
	else if (!ft_strcmp(command->cmd_name, "env"))
		return (env(core));
	else if (!ft_strcmp(command->cmd_name, "export"))
		return (export(core, command));
	else if (!ft_strcmp(command->cmd_name, "unset"))
		return (unset(core, command));
	else if (!ft_strcmp(command->cmd_name, "cd"))
		return (cd(core, command));
	return (0);
}

int	is_builtin(t_command *command)
{
	if (ft_strcmp(command->cmd_name, "cd")
		&& ft_strcmp(command->cmd_name, "echo")
		&& ft_strcmp(command->cmd_name, "env")
		&& ft_strcmp(command->cmd_name, "exit")
		&& ft_strcmp(command->cmd_name, "export")
		&& ft_strcmp(command->cmd_name, "pwd")
		&& ft_strcmp(command->cmd_name, "unset"))
		return (FALSE);
	return (TRUE);
}
