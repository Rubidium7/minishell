/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlonka <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 09:24:10 by nlonka            #+#    #+#             */
/*   Updated: 2023/08/15 10:55:34 by nlonka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include <termios.h>
# include <signal.h>

typedef enum e_error
{
	SUCCESS,
	FAILURE,
	SETUP_ERROR,
	TOKEN_ERROR,
	PARSE_ERROR
} t_error_code;

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
	WHITESPACE
} t_token_type;

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
	t_token_type	type;
	char			*content;
	int				quote;
	int				open_quote;
	struct s_token	*next;
}	t_token;

typedef struct s_info
{
	char	*input_line;
	char	**env;
	int		ret;
}	t_info;

typedef struct s_shell
{
	t_terminal	term;	
	t_sig		signals;
	t_token		*tokens;
	t_info		info;
}	t_shell;

#endif
