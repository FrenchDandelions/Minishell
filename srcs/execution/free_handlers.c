/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_handlers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thole <thole@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 17:44:18 by thole             #+#    #+#             */
/*   Updated: 2024/03/20 17:44:19 by thole            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	free_array(char **array)
{
	int	i;

	i = 0;
	while (array[i] != NULL)
	{
		free(array[i]);
		i++;
	}
	free(array);
	return ;
}

void	exit_error(char *str)
{
	ft_dprintf(2, "%s", str);
	exit(1);
}

void	exit_error_array(char *str, t_struct *s, char *s1, int index)
{
	if (index == 1 && !s1)
		ft_putstr_fd(s->tab[0], STDERR_FILENO);
	else if (index == 1 && s1 && !s1[0])
		ft_putstr_fd(s1, STDERR_FILENO);
	ft_putendl_fd(str, STDERR_FILENO);
	if (index == 1)
		free_all(s, 127);
	free_all(s, -2);
}

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab && tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

char	**dup_array(char **tab)
{
	char	**dup;
	int		i;

	i = 0;
	dup = NULL;
	while (tab && tab[i])
		i++;
	dup = malloc(sizeof(char *) * (i + 1));
	if (!dup)
		return (NULL);
	i = 0;
	while (tab && tab[i])
	{
		dup[i] = ft_strdup(tab[i]);
		if (!dup[i])
			return (free_tab(dup), NULL);
		i++;
	}
	dup[i] = NULL;
	return (dup);
}
