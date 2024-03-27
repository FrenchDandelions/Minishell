/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thole <thole@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 17:32:39 by thole             #+#    #+#             */
/*   Updated: 2024/03/20 17:32:40 by thole            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

static char	*get_color(int i)
{
	int	temp;

	temp = i % 7;
	if (temp == 0)
		return (RED);
	else if (temp == 1)
		return (ORANGE);
	else if (temp == 2)
		return (YELLOW);
	else if (temp == 3)
		return (GREEN);
	else if (temp == 4)
		return (LIGHTB);
	else if (temp == 5)
		return (BLUE);
	return (PURP2);
}

int	sort_and_print_env(char **env, int i, int j)
{
	char	*temp;

	while (env[i])
	{
		j = 0;
		while (env[j + 1])
		{
			if (env[j + 1] && ft_strcmp(env[j], env[j + 1]) > 0)
			{
				temp = env[j];
				env[j] = env[j + 1];
				env[j + 1] = temp;
			}
			j++;
		}
		i++;
	}
	i = 0;
	while (env[i])
	{
		printf("%s%s\n%s", get_color(i), env[i], RESET);
		i++;
	}
	return (SUCCESS);
}

int	printf_and_exit_export(t_struct *s, int i)
{
	ft_dprintf(2, "%sMinishell: export: '%s': not a valid identifier\n", RED,
		s->tab[i], RESET);
	s->exit_val = 1;
	if (s->tab[i + 1])
		return (export_check_value(s, i + 1));
	return (SUCCESS);
}

int	export_value(t_struct *s, int i, int j)
{
	char	*str;

	str = ft_strdup(s->tab[i]);
	if (!str)
	{
		ft_dprintf(2, "Malloc env export\n");
		free_all(s, -2);
	}
	free(s->env[j]);
	s->env[j] = str;
	if (!s->exit_val)
		s->exit_val = 0;
	return (SUCCESS);
}

int	new_value(t_struct *s, int i, int j)
{
	if (j == s->size_env)
	{
		s->env = ft_realloc_tab(s->env, sizeof(char *) * (s->size_env + 2),
				sizeof(char *) * s->size_env);
		if (!s->env)
		{
			ft_dprintf(2, "Malloc env export\n");
			free_all(s, -2);
		}
		s->size_env += 2;
	}
	s->env[j] = ft_strdup(s->tab[i]);
	if (!s->env[j])
	{
		ft_dprintf(2, "Malloc env\n");
		free_all(s, -2);
	}
	if (s->tab[i + 1])
		return (export_check_value(s, i + 1));
	return (SUCCESS);
}
