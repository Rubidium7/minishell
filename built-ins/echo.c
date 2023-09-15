/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvagapov <vvagapov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 21:26:14 by vvagapov          #+#    #+#             */
/*   Updated: 2023/09/15 20:35:58 by vvagapov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_bool	is_minus_n(const char *str)
{
	int	i;
	
	if (str[0] != '-' || str[1] != 'n')
		return (FALSE);
	i = 2;
	while (str[i])
	{
		if (str[i] != 'n')
			return (FALSE);
		i++;
	}
	return (TRUE);
}

int	echo(t_command *command)
{
	int		i;
	t_bool	no_newline;

	i = 1;
	no_newline = FALSE;
	while (is_minus_n(command->cmd_ar[i]) == TRUE)
	{
		no_newline = TRUE;
		i++;
	}
	//no -n option here
	while (command->cmd_ar[i])
	{
		printf("%s", command->cmd_ar[i]);
		if (command->cmd_ar[i + 1])
			printf(" ");
		i++;
	}
	if (!no_newline)
		printf("\n");
	return (0);
}
