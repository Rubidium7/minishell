
#include "minishell.h"


t_bool	expand_envs(t_token *head, t_shell *core)
{
	t_token	*current;
	char	*old_content;

	current = head;
	while (current)
	{
		//print_token(current, OFF); //debug
		//printf(" [%d]\n", current->after_redir); //debug
		if (current->type == WORD && current->after_redir != HEREDOC)
		{
			old_content = ft_strdup(current->content);
			if (!old_content)
				return (TRUE);
			current->content = expand_envs_in_string(current->content, core);
			if (!current->content)
				return (free(old_content), TRUE);
			//printf("content is '%s'\n", current->content); //debug
			if (current->after_redir && !current->content[0] && old_content[0])
			{
				current->ambiguity = TRUE;
				current->filename = old_content;	
			}
			else
				free(old_content);
		}
		current = current->next;
	}
	return (FALSE);
}