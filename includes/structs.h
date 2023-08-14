/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlonka <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 09:24:10 by nlonka            #+#    #+#             */
/*   Updated: 2023/08/14 18:37:56 by nlonka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include <termios.h>
# include <signal.h>

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

typedef struct s_token
{
	char	*cmd_name;
	char	**cmd_ar;
	int		red_in;
	int		red_out;
}	t_token;

typedef struct s_info
{
	char	*input_line;
	char	*history_buffer;
	char	**env;
	int		ret;
}	t_info;

enum Error
{
	SUCCESS,
	FAILURE,
	SETUP_ERROR
} error_codes;

typedef struct s_shell
{
	t_terminal	term;	
	t_sig		signals;
	t_token		tokens;
	t_info		info;
}	t_shell;

#endif
