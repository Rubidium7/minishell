/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exiting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlonka <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 11:31:56 by nlonka            #+#    #+#             */
/*   Updated: 2023/08/21 11:32:01 by nlonka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_exit(t_shell *core)
{
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &core->term.old);
	free(core->tmp_dir);
	free_ar(core->env);
	return (core->cur_process.ret);
}
