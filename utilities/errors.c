/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlonka <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 17:06:16 by nlonka            #+#    #+#             */
/*   Updated: 2023/08/15 18:57:03 by nlonka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	error_print(t_error_code type)
{
	if (type == TOKEN_ERROR)
		ft_putstr_fd("ERROR in tokenizing process🕷🕸", 2);
}
