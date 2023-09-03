

#include "minishell.h"




// void	open_redirections(t_command *new, t_pipeline *pipeline, t_shell *core)
// {
// 	t_token	*current;

// 	current = pipeline->start;
// 	while (current != pipeline->end)
// 	{
// 		if (is_redir(current->type))
// 		{
// 			if (current->type == RED_IN)
// 				open_infile(new, current);
// 			else if (current->type == RED_OUT || current->type == RED_OUT_APP)
// 				open_outfile(new, current);
// 		}
// 		current = current->next;
// 	}

// }