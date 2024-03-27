/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   go_home.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thole <thole@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 17:25:47 by thole             #+#    #+#             */
/*   Updated: 2024/03/20 17:25:49 by thole            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

char	*find_home_in_env(char **env, char *to_find)
{
	int	i;
	int	j;

	i = 0;
	while (env[i])
	{
		j = 0;
		if (check_if_is_in_env2(env[i], to_find))
		{
			while (env[i][j] != '=')
				j++;
			return (ft_substr(env[i], j + 1, (int)ft_strlen(env[i]) - j));
		}
		i++;
	}
	return (ft_strdup(""));
}

static int	return_home_issue(t_struct *s, int check)
{
	if (check == 1)
	{
		ft_dprintf(STDERR_FILENO, "Minishell: cd: HOME not set\n");
		s->exit_val = 1;
	}
	else
	{
		ft_dprintf(STDERR_FILENO, "Malloc\n");
		s->exit_val = -2;
	}
	return (check);
}

int	go_home(t_struct *s)
{
	char	*home;
	char	pwd[PATH_MAX];
	int		check;

	check = 0;
	home = find_home_in_env(s->env, "HOME");
	if (!home)
	{
		if (s->count_pipes)
			return (ft_dprintf(STDERR_FILENO, "Malloc\n"), free_all(s, -2), -2);
		return (return_home_issue(s, -2));
	}
	if (!home[0])
	{
		if (s->count_pipes)
			return (err_home(s, home));
		return (return_home_issue(s, 1));
	}
	if (!getcwd(pwd, PATH_MAX))
		check = 1;
	if (chdir(home))
		return (free_error_cd(s, home));
	if (change_paths(s, pwd, check) == ERR_MALLOC)
		return (ft_dprintf(STDERR_FILENO, "Malloc\n"), free_cd(s, home), -2);
	return (free_cd(s, home));
}
