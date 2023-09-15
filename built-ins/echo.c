/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvagapov <vvagapov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 21:26:14 by vvagapov          #+#    #+#             */
/*   Updated: 2023/09/15 19:31:16 by vvagapov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	echo(t_command *command)
{
	int i;

	i = 1;
	//no -n option here
	while (command->cmd_ar[i])
	{
		printf("%s", command->cmd_ar[i]);
		if (command->cmd_ar[i + 1])
			printf(" ");
		i++;
	}
	printf("\n");
	return (0);
}
