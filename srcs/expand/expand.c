/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   norm_expand.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thole <thole@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 16:53:45 by thole             #+#    #+#             */
/*   Updated: 2024/03/21 16:53:47 by thole            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	expand_single(char *string, char *str, int *i, int *j)
{
	if (str[(*i)] == '\'')
	{
		ft_sprintf(string + (*j), "%c", str[(*i)]);
		(*i)++;
		(*j)++;
		while (str[(*i)] && str[(*i)] != '\'')
		{
			ft_sprintf(string + (*j), "%c", str[(*i)]);
			(*i)++;
			(*j)++;
		}
		if (str[(*i)] && !is_quotes(str[(*i)]))
		{
			ft_sprintf(string + (*j), "%c", str[(*i)]);
			(*i)++;
			(*j)++;
		}
	}
}

int	get_dups_values(char **dup, char **dup2, t_struct *s, char *str)
{
	int	len;

	len = 0;
	get_len_variable(str, &len, s);
	if (len == 0 && s->i_n_quotes)
	{
		(*dup) = ft_strdup("");
		if (!(*dup))
			return (ERR_MALLOC);
		(*dup2) = find_in_path((*dup), s->env, 0, s);
		if (!(*dup2))
			return (free((*dup)), ERR_MALLOC);
	}
	else
	{
		(*dup) = ft_substr(str, s->x_i, len);
		if (!(*dup))
			return (ERR_MALLOC);
		(*dup2) = find_in_path((*dup), s->env, 1, s);
		if (!(*dup2))
			return (free((*dup)), ERR_MALLOC);
	}
	return (SUCCESS);
}

int	expand_dollars(char **string, char *str, char **env, t_struct *s)
{
	char	*dup;
	char	*dup2;
	int		len;

	dup = NULL;
	dup2 = NULL;
	(void)env;
	if (str[s->x_i] == '$')
	{
		len = 0;
		s->x_i++;
		get_len_variable(str, &len, s);
		if (get_dups_values(&dup, &dup2, s, str) == ERR_MALLOC)
			return (free((*string)), ERR_MALLOC);
		*string = ft_realloc(*string, sizeof(char) * (ft_strlen(dup2)
					+ ft_strlen(*string) + ft_strlen(str)), ft_strlen(*string));
		if (!*string)
			return (ERR_MALLOC);
		ft_sprintf(*string + s->x_j, "%s", dup2);
		s->x_j += (int)ft_strlen(dup2);
		s->x_i += len;
		delete_strings(dup, dup2);
	}
	return (SUCCESS);
}

int	expand_double(char **string, char *str, t_struct *s, char **env)
{
	if (str[s->x_i] == '\"')
	{
		s->i_n_quotes = 1;
		ft_sprintf(*string + s->x_j, "%c", str[s->x_i]);
		s->x_i++;
		s->x_j++;
		while (str[s->x_i] && str[s->x_i] != '\"')
		{
			if (expand_dollars(&(*string), str, env, s) == ERR_MALLOC)
				return (ERR_MALLOC);
			if (str[s->x_i] && str[s->x_i] != '$' && str[s->x_i] != '\"')
			{
				ft_sprintf(*string + s->x_j, "%c", str[s->x_i]);
				s->x_i++;
				s->x_j++;
			}
		}
		if (str[s->x_i] && !is_quotes(str[s->x_i]))
		{
			ft_sprintf(*string + s->x_j, "%c", str[s->x_i]);
			s->x_i++;
			s->x_j++;
		}
	}
	return (SUCCESS);
}

char	*expand(char *str, char **env, t_struct *s)
{
	char	*string;
	int		i;
	int		j;

	j = 0;
	i = 0;
	get_indexes(&i, &j, s, 0);
	string = ft_calloc(sizeof(char), (ft_strlen(str) + 1));
	if (!string)
		return (NULL);
	while (str[i])
	{
		expand_single(string, str, &i, &j);
		get_indexes(&i, &j, s, 0);
		if (expand_double(&string, str, s, env) == ERR_MALLOC)
			return (NULL);
		get_indexes(&i, &j, s, 1);
		get_indexes(&i, &j, s, 0);
		if (expand_dollars(&string, str, env, s) == ERR_MALLOC)
			return (NULL);
		get_indexes(&i, &j, s, 1);
		get_indexes(&i, &j, s, 0);
		add_to_buff(string, str, &i, &j);
	}
	return (string);
}
