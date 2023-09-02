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
	core->cur_process.heredoc_index = 0;
	core->tokens = tokenize(input);
	if (!core->tokens)
		return ;
	//print_token_list(core->tokens, ON); //debug
	if (!core->tokens->next)
		return (free(core->tokens));
	if (preliminary_syntax_check(core))
		return (free(core->tokens));
	if (save_redirection_filenames(core->tokens))
		return (empty_token_list(core->tokens));
	indexify_token_list(core->tokens);
	//print_token_list(core->tokens, OFF); //debug
	parse(core);
	if (!core->cur_process.tree)
		return (empty_token_list(core->tokens));
	//print_token_list(core->tokens, OFF); //debug
//	if (!core->cur_process.tree_head)
//		return ;
	//execute
	clean_up(core);
}
