/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvagapov <vvagapov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 10:21:30 by nlonka            #+#    #+#             */
/*   Updated: 2023/09/18 17:38:41 by vvagapov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINES_H
# define DEFINES_H

# define INT_MAX 2147483647
# define INT_MIN -2147483648
# define LL_INT_MAX 9223372036854775807
# define LL_INT_MIN -9223372036854775807
# define HISTORY_MAX 500
# define PATH_MAX_LEN 4096
# define SHROOM_TIME 37
# define YES 1
# define NO 0
# define EXPORT 1
# define ENV 2

//different colour codes
//R red
//W white
//G green
//M magenta
//CY cyan
//B blue
//wr is white bg red text and rw is the other way around
# define R "\033[1;31m"
# define W "\033[1;37m"
# define G "\033[1;32m"
# define Y "\033[1;33m"
# define M "\033[1;35m"
# define CY "\033[1;36m"
# define B "\033[1;34m"
# define RW "\033[1;31;47m"
# define WR "\033[1;37;41m"
# define C "\033[0m"

# define MINI_SHROOM "🍄\033[1;37mMini\033[1;31mShroom\033[0m"
# define ERROR_SHROOM "🐛 🕸\033[1;31mError\033[1;37m🕸Shroom: \033[0m"

# define HISTORY_FILE ".shell_history.tmp"

#endif
