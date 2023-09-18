/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_matching.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlonka <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 15:13:58 by nlonka            #+#    #+#             */
/*   Updated: 2023/09/14 15:14:00 by nlonka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	incrementer(int *int1, int *int2)
{
	*int1 += 1;
	*int2 += 1;
}

static void	assign_numbers(int *fi, int *wi, int *back, int next_to_wild)
{
	*wi = next_to_wild;
	*fi = ++(*back);
}

t_bool	backtrack_wildcards(char *file, char *wild_str, int *fi, int *wi)
{
	int			last_wild;
	int			back;
	int			next_to_wild;

	last_wild = -1;
	back = -1;
	next_to_wild = -1;
	while (file[*fi])
	{
		if (wild_str[*wi] && file[*fi] == wild_str[*wi])
			incrementer(fi, wi);
		else if (wild_str[*wi] == 1)
		{
			last_wild = *wi;
			next_to_wild = ++(*wi);
			back = *fi;
		}
		else if (last_wild == -1)
			return (FALSE);
		else
			assign_numbers(fi, wi, &back, next_to_wild);
	}
	return (TRUE);
}

t_bool	is_wildcard_match(char *file, t_wildcard *wildcard)
{
	int			fi;
	int			wi;
	char		*wild_str;

	wild_str = format_wildcard_into_string(wildcard);
	if (!wild_str)
		return (error_print(WILDCARD_ERROR), FALSE);
	fi = 0;
	wi = 0;
	if (!backtrack_wildcards(file, wild_str, &fi, &wi))
		return (free(wild_str), FALSE);
	while (wild_str[wi])
	{
		if (wild_str[wi] != 1)
			return (free(wild_str), FALSE);
		wi++;
	}
	return (free(wild_str), TRUE);
}
