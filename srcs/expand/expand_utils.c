/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aattali <aattali@student.42.fr>             +#+  +:+       +#+       */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 16:34:31 by aattali             #+#    #+#           */
/*   Updated: 2024/03/27 14:57:55 by andrew           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	is_quotes(int c)
{
	if (c == '\'' || c == '\"')
		return (1);
	return (0);
}

void	delete_strings(char *s1, char *s2)
{
	if (s1)
		ft_memdel(s1);
	if (s2)
		ft_memdel(s2);
}

char	*takeoff_quotes(char *str)
{
	char	*dup;
	char	type;
	int		i;
	int		j;

	dup = ft_calloc(sizeof(char), ft_strlen(str) + 1);
	if (!dup)
		return (free(str), NULL);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (is_quotes(str[i]))
		{
			type = str[i++];
			while (str[i] && str[i] != type)
				dup[j++] = str[i++];
			if (str[i] == type)
				i++;
		}
		if (str[i] && !is_quotes(str[i]))
			dup[j++] = str[i++];
	}
	return (free(str), dup);
}

int	is_alnum_undescore(int c)
{
	if (ft_isalnum(c) || c == '_')
		return (1);
	return (0);
}

int	expand_condition_value(t_struct *s, char *str, int len)
{
	if ((len == 0 && s->i_n_quotes))
		return (1);
	else if ((len == 0 && (!str[s->x_i] || !str[s->x_i + 1]) && !s->i_n_quotes)
		|| (len == 0 && str[s->x_i] && str[s->x_i] == '$'))
		return (1);
	return (0);
}
