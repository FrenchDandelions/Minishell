/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thole <thole@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 16:35:33 by thole             #+#    #+#             */
/*   Updated: 2024/03/20 16:35:35 by thole            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	get_env(char **env, t_struct *s)
{
	int	i;

	i = 0;
	while (env[i])
		i++;
	s->env = (char **)malloc(sizeof(char *) * (i + 1));
	if (!s->env)
		return (ERR_MALLOC);
	i = 0;
	while (env[i])
	{
		s->env[i] = ft_strdup(env[i]);
		if (!s->env[i])
			return (free_env(s->env), ERR_MALLOC);
		i++;
	}
	s->env[i] = NULL;
	s->size_env = i;
	return (SUCCESS);
}

int	init_env(t_struct *s, char **env)
{
	if (get_env(env, s) == ERR_MALLOC)
		return (ft_dprintf(2, "Malloc\n"), -2);
	s->dup_env = dup_array(s->env);
	if (!s->dup_env)
		return (ft_dprintf(2, "Malloc\n"), -2);
	return (SUCCESS);
}
