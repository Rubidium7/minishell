/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_atoi.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvagapov <vvagapov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 22:35:10 by vvagapov          #+#    #+#             */
/*   Updated: 2023/09/18 23:01:34 by vvagapov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static long long int	set_overflow(int *overflow)
{
	*overflow = 1;
	return (2);
}

long long int	slightly_special_atoi(char *str, int *overflow)
{
	long long int	res;
	long long int	prev_res;
	int				i;
	int				sign;

	if (!ft_strcmp("-9223372036854775808", str))
		return (LL_INT_MIN - 1);
	sign = 1;
	i = 0;
	res = 0;
	if (str[0] == '-')
	{
		sign = -1;
		i++;
	}
	while (str[i])
	{
		prev_res = res;
		res = res * 10 + (str[i] - '0');
		if (prev_res > res)
			return (set_overflow(overflow));
		i++;
	}
	return (sign * res);
}
