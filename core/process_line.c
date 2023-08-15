/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlonka <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 10:52:43 by nlonka            #+#    #+#             */
/*   Updated: 2023/08/15 18:44:43 by nlonka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	process_line(t_shell *core, char *input)
{
	core->tokens = tokenize(input);
	print_token_list(core->tokens);
	if (!core->tokens)
		return (error_print(TOKEN_ERROR));
	//syntax check
	//create tree
	//expand environment variables while going through tree
	//execute
	//clean
}
