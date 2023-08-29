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
	core->cur_process.tree = syntax_check(core->tokens->next, core);
	if (!core->cur_process.tree)
		return ;
	print_tree_in_execution_order(core->cur_process.tree); //debug
	//https://i.kym-cdn.com/photos/images/newsfeed/001/889/888/265.jpeg
}
