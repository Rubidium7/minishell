/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlonka <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 10:32:51 by nlonka            #+#    #+#             */
/*   Updated: 2023/08/14 10:33:03 by nlonka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parse(t_shell *core)
{
	t_ast	*tree;

	tree = syntax_check(core->tokens, &core->cur_process.ret);
	if (!tree)
		return ;
}
