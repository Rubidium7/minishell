/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exiting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlonka <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 18:33:49 by nlonka            #+#    #+#             */
/*   Updated: 2023/08/14 19:10:25 by nlonka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_exit(t_shell *core)
{
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &core->term.old);
	free_ar(core->env);
	return (core->cur_process.ret);
}
