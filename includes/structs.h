/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvagapov <vvagapov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 09:24:10 by nlonka            #+#    #+#             */
/*   Updated: 2023/09/12 13:23:03 by vvagapov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include <termios.h>
# include <signal.h>

typedef enum e_bool
{
	FALSE,
	TRUE
} t_bool;

typedef enum e_error
{
	SUCCESS,
	FAILURE,
	NO_RIGHTS,
	NO_FILE,
	AMBIGUOUS,
	HEREDOC_FILE_ERROR,
	SYNTAX_ERROR = 258,
	MALLOC_ERROR,
	PIPE_ERROR,
	OPEN_ERROR,
	SETUP_ERROR,
	TOKEN_ERROR,
	PARSE_ERROR,
	HEREDOC_ERROR,
	WILDCARD_ERROR,
	EXEC_ERROR,
} t_error_code;

typedef enum e_internal_values
{
	OFF,
	ON,
	NOT_OPEN = -1,
	DEFAULT = -2,
	MALLOC_FAIL = -3,
	PARENTHESES_ERROR = -4,
	NO_LOGIC = -5,
	NOT_FOUND = -6,
	PIPE_FAIL = -7,
} t_internal_values;

typedef enum e_syntax_error
{
	UNEXPECTED_NL = -4,
	UNEXPECTED_TOKEN = 1,
	OPEN_QUOTE,
	OPEN_PARENTHESES
} t_syntax_error;

typedef enum e_token
{
	HEAD,
	WORD,
	RED_IN,
	HEREDOC,
	RED_OUT,
	RED_OUT_APP,
	PIPE,
	OR,
	AMPERSAND,
	AND,
	LPAR,
	RPAR,
	WHITESPACE,
	EMPTY
} t_token_type;

typedef struct s_terminal
{
	struct termios	new;
	struct termios	old;

}	t_terminal;

typedef struct s_wildcard
{
	char				*str;
	t_bool				expand;
	struct s_wildcard	*next;
}	t_wildcard;

typedef struct s_command
{
	char				*cmd_name;
	char				**cmd_ar;
	int					red_in;
	int					red_out;
	int					index;
	struct s_command	*next;
}	t_command;

typedef struct s_token
{
	int				position;
	t_token_type	type;
	char			*content;
	char			*filename;
	int				quote;
	t_bool			open_quote;
	t_bool			ambiguity;
	int				after_redir;
	t_wildcard		*wildcard;
	struct s_token	*next;
}	t_token;

typedef struct s_pipeline
{
	t_token				*start;
	t_token				*end;
	struct s_pipeline	*next;
}	t_pipeline;

typedef struct s_heredoc
{
	int					index;
	char				*filename;
	struct s_heredoc	*next;
}	t_heredoc;

typedef struct s_ast
{
	t_pipeline		*pipeline;
	t_command		*command_list;
	t_token_type	type;
	int				return_value;
	t_heredoc		*heredoc_list;
	struct s_ast	*up;
	struct s_ast	*right;
	struct s_ast	*left;
}	t_ast;

typedef struct s_current_process
{
	char	*input_line;
	int		error_index;
	int		heredoc_index;
	t_bool	terminated;
	t_ast	*tree;
	t_bool	shroom_time;
	int		ret;
}	t_current_process;

typedef struct s_env
{
	char			*key;
	char			*content;
	struct s_env	*next;
}	t_env;

typedef struct s_shell
{
	t_terminal			term;
	t_token				*tokens;
	t_current_process	cur_process;
	t_env				*env_list;
	char				**env; //to be replaced
}	t_shell;

#endif
