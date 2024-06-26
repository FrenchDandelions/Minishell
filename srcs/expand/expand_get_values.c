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

char	*find_in_path(char *needle, char **env, int len, t_struct *s)
{
	int		size;
	int		i;
	char	*str;

	size = (int)ft_strlen(needle);
	i = 0;
	if (size == 1 && needle[0] == '?')
		return (ft_itoa(s->exit_val));
	while (env[i] && needle[0])
	{
		if (ft_strnstr(env[i], needle, size))
		{
			str = ft_strdup(env[i] + 1 + size);
			return (str);
		}
		i++;
	}
	if (len == 0 && size == 0)
		return (ft_strdup("$"));
	return (ft_strdup(""));
}

void	set_new_indexes(int *i, int *j, t_struct *s)
{
	s->i_n_quotes = 0;
	get_indexes(&(*i), &(*j), s, 1);
	get_indexes(&(*i), &(*j), s, 0);
}

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
	s->i_n_quotes = 0;
	if (try == 0)
	{
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
