/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlonka <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 10:52:43 by nlonka            #+#    #+#             */
/*   Updated: 2023/08/16 13:52:07 by nlonka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	process_line(t_shell *core, char *input)
{
	core->tokens = tokenize(input);
	print_token_list(core->tokens, ON); //debug
	if (!core->tokens)
		return (error_print(TOKEN_ERROR));
	if (!core->tokens->next)
		return (free(core->tokens));
	indexify_token_list(core->tokens);
	parse(core);
	if (!core->cur_process.tree_head)
		return ;
	//execute
	clean_up(core);
}
