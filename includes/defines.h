/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlonka <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 10:21:30 by nlonka            #+#    #+#             */
/*   Updated: 2023/08/14 18:55:28 by nlonka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINES_H
# define DEFINES_H

# define ON 1
# define OFF 0
# define INT_MAX 2147483647
# define INT_MIN -2147483648

//different colour codes
//R red
//W white
//G green
//M magenta
//wr is white bg red text and rw is the other way around
# define R "\033[0;31m"
# define B "\033[0;34m"
# define M "\033[0;35m"
# define W "\033[1;37m"
# define RW "\033[1;31;47m"
# define WR "\033[1;37;41m"
# define C "\033[0m"

# define ERROR_SHROOM R"🕸Error"C W"🕸Shroom: "C

#endif
