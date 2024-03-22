/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thole <thole@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 17:19:52 by thole             #+#    #+#             */
/*   Updated: 2024/03/20 17:19:53 by thole            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

int	is_full_of_n(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-')
		i++;
	else
		return (0);
	while (str[i] == 'n')
		i++;
	if (str[i])
		return (0);
	return (1);
}

int	find_option(char **tab)
{
	int	i;

	i = 0;
	while (tab[i] && tab[i + 1])
	{
		if (!is_full_of_n(tab[i + 1]))
			break ;
		if (ft_strchr(tab[i + 1], '-') && is_full_of_n(tab[i + 1]))
			return (i + 1);
		i++;
	}
	return (i);
}

int	n_case(t_struct *s)
{
	int	i;
	int	j;

	i = 1;
	j = find_option(s->tab);
	if (j)
	{
		while (s->tab[i] && s->tab[i + 1])
		{
			if (i == j)
				i++;
			if (!is_full_of_n(s->tab[i]) && s->tab[i + 1] && (i + 1) != j)
				printf("%s ", s->tab[i]);
			else if ((i + 1) == j)
				printf("%s", s->tab[i]);
			if (s->tab[i + 1])
				i++;
		}
		if (i != j && s->tab[i])
			printf("%s", s->tab[i]);
	}
	return (j);
}

void	ft_echo(t_struct *s)
{
	int	i;

	i = 1;
	if (!s->tab[1])
		printf("\n");
	else if (!n_case(s))
	{
		while (s->tab[i] && s->tab[i + 1])
		{
			printf("%s ", s->tab[i]);
			i++;
		}
		printf("%s\n", s->tab[i]);
	}
	free_all(s, 0);
}
