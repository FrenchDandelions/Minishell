/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thole <thole@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 17:32:45 by thole             #+#    #+#             */
/*   Updated: 2024/03/20 17:32:46 by thole            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

int	check_if_is_in_env(char *env_line, char *var)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	while (env_line[i] && var[j] && env_line[i] != '=' && var[j] != '='
		&& env_line[i] == var[j])
	{
		i++;
		j++;
	}
	if (env_line[i] == '=' && var[j] == '=')
		return (1);
	return (0);
}

int	loop_export(t_struct *s, int i, int *j)
{
	while (s->env[(*j)])
	{
		if (check_if_is_in_env(s->env[(*j)], s->tab[i]))
		{
			if (export_value(s, i, (*j)) == ERR_MALLOC)
				free_all(s, -2);
			if (s->tab[i + 1])
				return (export_check_value(s, i + 1));
			return (SUCCESS);
		}
		(*j)++;
	}
	return (SUCCESS);
}

int	export_check_value(t_struct *s, int i)
{
	int	j;
	int	k;

	j = 0;
	k = 0;
	while (s->tab[i][k] && is_alnum_undescore(s->tab[i][k])
		&& !ft_isdigit(s->tab[i][0]))
		k++;
	if (k == 0 || (s->tab[i][k] && s->tab[i][k] != '='))
		return (printf_and_exit_export(s, i));
	if (!s->tab[i][k] && !s->tab[i + 1])
		return (SUCCESS);
	else if (!s->tab[i][k] && s->tab[i + 1])
		return (export_check_value(s, i + 1));
	if (loop_export(s, i, &j) == ERR_MALLOC)
		return (ERR_MALLOC);
	if (!s->env[j])
		return (new_value(s, i, j));
	return (SUCCESS);
}

int	ft_export_notchild(t_struct *s, char **env)
{
	(void)env;
	s->exported = 1;
	if (!s->tab[1])
		return (sort_and_print_env(s->env, 0, 0));
	return (export_check_value(s, 1));
}

void	ft_export(t_struct *s, char **env)
{
	(void)env;
	if (!s->tab[1])
		sort_and_print_env(s->env, 0, 0);
	else
		export_check_value(s, 1);
	free_all(s, 0);
}
