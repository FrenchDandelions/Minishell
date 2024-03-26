/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thole <thole@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 12:30:17 by thole             #+#    #+#             */
/*   Updated: 2024/03/19 12:30:18 by thole            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

int	find_path_cd(t_struct *s)
{
	char	pwd[PATH_MAX];
	int		check;

	check = 0;
	if (!getcwd(pwd, PATH_MAX))
		check = 1;
	if (s->tab[1][0])
	{
		if (chdir(s->tab[1]))
			return (free_error_cd(s, NULL));
	}
	else
	{
		if (chdir("."))
			return (free_error_cd(s, NULL));
	}
	if (change_paths(s, pwd, check) == ERR_MALLOC)
		return (ft_dprintf(STDERR_FILENO, "Malloc\n"), free_cd(s, NULL), -2);
	return (free_cd(s, NULL));
}

int	change_old(t_struct *s, char *oldpwd, int check)
{
	int		i;
	char	*str;

	i = 0;
	while (s->env[i])
	{
		if (check_if_is_in_env2(s->env[i], "OLDPWD"))
		{
			if (check)
				return (SUCCESS);
			str = ft_strjoin("OLDPWD=", oldpwd);
			if (!str)
				return (ERR_MALLOC);
			free(s->env[i]);
			s->env[i] = str;
		}
		i++;
	}
	return (SUCCESS);
}

int	change_new(t_struct *s, char *pwd, int check)
{
	int		i;
	char	*str;

	i = 0;
	while (s->env[i])
	{
		if (check_if_is_in_env2(s->env[i], "PWD"))
		{
			if (check)
				return (SUCCESS);
			str = ft_strjoin("PWD=", pwd);
			if (!str)
				return (ERR_MALLOC);
			free(s->env[i]);
			s->env[i] = str;
		}
		i++;
	}
	return (SUCCESS);
}

int	change_paths(t_struct *s, char *oldpwd, int check)
{
	char	pwd[PATH_MAX];

	if (change_old(s, oldpwd, check) == ERR_MALLOC)
		return (ERR_MALLOC);
	check = 0;
	if (!getcwd(pwd, PATH_MAX))
	{
		ft_dprintf(STDERR_FILENO, "cd: error retrieving current directory: ");
		perror(ERR_CD);
		s->exit_val = 1;
		s->error_cd = 1;
		check = 1;
	}
	else if (change_new(s, pwd, check) == ERR_MALLOC)
		return (ERR_MALLOC);
	return (SUCCESS);
}

void	ft_cd(t_struct *s)
{
	int	stat;

	if (!s->tab[1])
		stat = go_home(s);
	else if (s->tab[2])
		stat = print_error_cd(s);
	else
		stat = find_path_cd(s);
	if (stat == ERR_MALLOC)
		ft_dprintf(STDERR_FILENO, "Fatal, malloc error in cd\n");
	if (s->count_pipes)
		free_all(s, 0);
}
