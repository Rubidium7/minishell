/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlonka <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 09:24:10 by nlonka            #+#    #+#             */
/*   Updated: 2023/08/20 21:48:29 by nlonka           ###   ########.fr       */
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
	SETUP_ERROR = 259,
	TOKEN_ERROR,
	PARSE_ERROR
} t_error_code;

typedef enum e_syntax_error
{
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

typedef enum e_ast
{
	PIPELINE = 1,
	WORDS,
	REDIRS,
	REDIR,
	LIST,
	AND_OR,
	TERMINAL,
	NEW_LINE_ERROR
} t_ast_type;

typedef struct s_terminal
{
	struct termios	new;
	struct termios	old;

}	t_terminal;

typedef struct s_sig
{
	struct sigaction	ignored;
	struct sigaction	ctrl_c;

}	t_sig;

typedef struct s_command
{
	char	*cmd_name;
	char	**cmd_ar;
	int		red_in;
	int		red_out;
}	t_command;

typedef struct s_token
{
	int				position;
	t_token_type	type;
	char			*content;
	int				quote;
	t_bool			open_quote;
	t_bool			new_line_error;
	struct s_token	*filename;
	struct s_token	*next;
}	t_token;

typedef struct s_ast
{
	t_token			*token;
	t_ast_type		type;
	struct s_ast	*up;
	struct s_ast	*right;
	struct s_ast	*left;
}	t_ast;

typedef struct s_current_process
{
	char	*input_line;
	t_ast	*tree_head;
	int		ret;
}	t_current_process;

typedef struct s_shell
{
	t_terminal			term;	
	t_sig				signals;
	t_token				*tokens;
	t_current_process	cur_process;
	char				**env;
}	t_shell;

#endif
