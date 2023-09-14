/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlonka <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 15:19:22 by nlonka            #+#    #+#             */
/*   Updated: 2023/09/14 15:20:12 by nlonka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	open_infile(t_command *new, t_token *current)
{
	if (new->red_in > 0)
		close(new->red_in);
	if (current->ambiguity)
		new->red_in = NOT_OPEN;
	else
		new->red_in = open(current->filename, O_RDONLY);
	if (new->red_in == NOT_OPEN)
	{
		if (current->ambiguity)
			print_file_error(current->filename, AMBIGUOUS);
		else if (!access(current->filename, F_OK))
			print_file_error(current->filename, NO_RIGHTS);
		else
			print_file_error(current->filename, NO_FILE);
	}
}

void	open_outfile(t_command *new, t_token *current)
{
	if (new->red_out > 0)
		close(new->red_out);
	if (current->ambiguity)
		new->red_out = NOT_OPEN;
	else if (current->type == RED_OUT)
		new->red_out = open(current->filename,
			   	O_WRONLY | O_CREAT | O_TRUNC, 0000644);
	else
		new->red_out = open(current->filename,
			   	O_WRONLY | O_CREAT | O_APPEND, 0000644);
	if (new->red_out == NOT_OPEN)
	{
		if (current->ambiguity)
			print_file_error(current->filename, AMBIGUOUS);
		else if (!access(current->filename, F_OK))
			print_file_error(current->filename, NO_RIGHTS);
		else
			print_file_error(current->filename, NO_FILE);
	}
}

void	update_heredoc(t_command *new, t_heredoc *heredoc)
{
	while (heredoc && heredoc->index != new->index)
		heredoc = heredoc->next;
	if (!heredoc)
		return ;
	if (new->red_in != DEFAULT)
		close(new->red_out);
	new->red_in = open(heredoc->filename, O_RDONLY);
	if (new->red_in == NOT_OPEN)
		print_file_error(NULL, HEREDOC_FILE_ERROR);
}

void	open_redirections(t_command *new, 
		t_pipeline *pipeline, t_heredoc *heredoc, t_shell *core)
{
	t_token	*current;

	current = pipeline->start;
	core->cur_process.ret = 0;
	while (current != pipeline->end)
	{
		if (is_redir(current->type) && current->type != HEREDOC)
		{
			if (current->type == RED_IN)
				open_infile(new, current);
			else if (current->type == RED_OUT || current->type == RED_OUT_APP)
				open_outfile(new, current);
			if (new->red_in == NOT_OPEN || new->red_out == NOT_OPEN)
			{
				core->cur_process.ret = 1;
				return ;
			}
		}
		current = current->next;
	}
	update_heredoc(new, heredoc);
	if (new->red_in == NOT_OPEN)
		core->cur_process.ret = 1;
}
