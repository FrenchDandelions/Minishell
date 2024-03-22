/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thole <thole@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 16:34:31 by thole             #+#    #+#             */
/*   Updated: 2024/03/22 16:34:32 by thole            ###   ########.fr       */
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
