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
	core->cur_process.error_index = DEFAULT;
	core->tokens = tokenize(input, core);
	if (!core->tokens)
	{
		core->cur_process.ret = MALLOC_ERROR;
		return (error_print(TOKEN_ERROR));
	}
	if (!core->tokens->next)
		return (empty_token_list(core->tokens));
	core->tokens = expand_wildcards(core->tokens);
	indexify_token_list(core->tokens);
	preliminary_syntax_check(core);
	save_redirection_filenames(core->tokens);
	wildcards_in_filenames(core->tokens);
	//print_token_list(core->tokens, ON); //debug
	parse(core);
	if (!core->cur_process.tree)
		return (empty_token_list(core->tokens));
	core->cur_process.error_index = DEFAULT;
	execute_tree(core->cur_process.tree, core);
	clean_up(core);
}
