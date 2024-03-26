/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thole <thole@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 14:54:45 by thole             #+#    #+#             */
/*   Updated: 2024/03/26 14:54:47 by thole            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int		expand_dollars(char **string, char *str, char **env, t_struct *s);

void	add_to_buff_hd(char *string, char *str, int *i, int *j)
{
	if (str[(*i)] && str[(*i)] != '$')
	{
		ft_sprintf(string + (*j), "%c", str[(*i)]);
		(*i)++;
		(*j)++;
	}
}

char	*expand_heredoc(char *str, char **env, t_struct *s)
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
		get_indexes(&i, &j, s, 0);
		if (expand_dollars(&string, str, env, s) == ERR_MALLOC)
			return (NULL);
		set_new_indexes(&i, &j, s);
		add_to_buff_hd(string, str, &i, &j);
	}
	return (string);
}
