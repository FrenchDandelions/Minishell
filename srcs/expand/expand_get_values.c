/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_get_values.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thole <thole@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 16:35:48 by thole             #+#    #+#             */
/*   Updated: 2024/03/22 16:35:49 by thole            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	add_to_buff(char *string, char *str, int *i, int *j)
{
	if (str[(*i)] && str[(*i)] != '$' && !is_quotes(str[(*i)]))
	{
		ft_sprintf(string + (*j), "%c", str[(*i)]);
		(*i)++;
		(*j)++;
	}
}

void	get_indexes(int *i, int *j, t_struct *s, int try)
{
	if (try == 0)
	{
		s->i_n_quotes = 0;
		s->x_i = *i;
		s->x_j = *j;
	}
	else if (try == 1)
	{
		*i = s->x_i;
		*j = s->x_j;
	}
}

void	get_len_variable(char *str, int *len, t_struct *s)
{
	while (str[s->x_i + (*len)] && (is_alnum_undescore(str[s->x_i + (*len)])
			|| ((*len) == 0 && str[s->x_i + (*len)] == '?')))
	{
		if ((*len) == 1 && str[s->x_i + (*len) - 1] == '?')
			break ;
		(*len)++;
	}
}
