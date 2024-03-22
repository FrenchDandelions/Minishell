/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thole <thole@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 17:45:51 by thole             #+#    #+#             */
/*   Updated: 2024/03/20 17:45:53 by thole            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_is_buildin(char *s)
{
	if (ft_strncmp("echo", s, 5) == 0)
		return (1);
	else if (ft_strncmp("export", s, 7) == 0)
		return (1);
	else if (ft_strncmp("cd", s, 3) == 0)
		return (1);
	else if (ft_strncmp("pwd", s, 4) == 0)
		return (1);
	else if (ft_strncmp("unset", s, 6) == 0)
		return (1);
	else if (ft_strncmp("env", s, 4) == 0)
		return (1);
	else if (ft_strncmp("exit", s, 5) == 0)
		return (1);
	return (0);
}

void	exec_buildin(t_struct *s, char **env, int i, char *cmd)
{
	if (ft_strncmp("echo", cmd, 5) == 0)
		ft_echo(s);
	else if (ft_strncmp("export", cmd, 7) == 0)
		ft_export(s, env);
	else if (ft_strncmp("cd", cmd, 3) == 0)
		ft_cd(s);
	else if (ft_strncmp("pwd", cmd, 4) == 0)
		ft_pwd(s);
	else if (ft_strncmp("unset", cmd, 6) == 0)
		ft_unset(s, env);
	else if (ft_strncmp("env", cmd, 4) == 0)
		ft_env(s, env, i);
	else if (ft_strncmp("exit", cmd, 5) == 0)
		ft_exit(s);
}

void	handle_errno(t_struct *s)
{
	int	err;

	err = errno;
	if (err == EACCES)
	{
		perror(s->tab[0]);
		errno = err;
		free_all(s, 126);
	}
	if (err == ENOENT)
	{
		perror(s->tab[0]);
		errno = err;
		free_all(s, 127);
	}
}
