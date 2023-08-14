/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_data.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlonka <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 10:33:41 by nlonka            #+#    #+#             */
/*   Updated: 2023/08/14 18:38:30 by nlonka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_start_data(t_shell *core, char **start_env)
{
	core->info.ret = 0;
	core->info.env = copy_array(start_env);
	if (!core->info.env)
		exit(SETUP_ERROR);
}
