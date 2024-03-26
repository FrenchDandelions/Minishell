/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thole <thole@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 13:15:13 by thole             #+#    #+#             */
/*   Updated: 2024/03/09 13:15:15 by thole            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

extern int	g_sig;

int	err_fork(int *pipe, int check)
{
	if (check == 0)
	{
		close(pipe[0]);
		close(pipe[1]);
		ft_dprintf(2, "fork\n");
		return (-1);
	}
	else if (check == 1)
	{
		ft_dprintf(2, "fork\n");
		return (-1);
	}
	return (SUCCESS);
}

void	exec_normal(t_struct *s, char **env)
{
	char	*path;
	int		i;

	i = 0;
	if (!s->tab[0] || !s->tab[0][0])
		exit_error_array(": command not found\n", s, NULL, 1);
	path = get_path(s->tab[0], env, &i);
	if (path == NULL)
		exit_error_array("malloc\n", s, path, 0);
	if (i == 2)
		exit_error_array("", s, path, 1);
	if (!path[0])
		exit_error_array(": command not found\n", s, path, 1);
	if (execve(path, s->tab, env) == -1)
	{
		handle_errno(s, path);
		ft_dprintf(2, "%s: command not found\n", s->tab[0]);
		free_all(s, 127);
	}
	if (g_sig == 130)
		free_all(s, 130);
	else if (g_sig == 131)
		free_all(s, 131);
	free_all(s, 0);
}

int	exec_path(t_struct *s, int index, int fake_env)
{
	char	*cmd;

	if (s->tab[0][0])
		cmd = s->tab[0];
	else
		cmd = s->tab[1];
	if (fake_env)
	{
		if (index == 1)
			exec_buildin(s, s->env, fake_env, cmd);
		else
			exec_normal(s, s->env);
	}
	else
	{
		if (index == 1)
			exec_buildin(s, s->env, fake_env, cmd);
		else
			exec_normal(s, s->env);
	}
	return (SUCCESS);
}

int	do_parent(t_struct *s)
{
	if (!s->is_first)
		close(s->last_fd);
	s->last_fd = s->pipe[0];
	if (s->counter != s->count_pipes)
		close(s->pipe[1]);
	g_sig = 0;
	return (SUCCESS);
}

int	exec(t_struct *s, t_file *file)
{
	if (s->counter != s->count_pipes)
		if (pipe(s->pipe) == -1)
			return (ft_dprintf(2, "pipe\n"), -1);
	sig_child();
	s->pid = fork();
	if (s->pid < 0)
		return (err_fork(s->pipe, 0));
	else if (!s->pid)
	{
		if (do_files(file, s))
			free_all(s, 1);
		if (!s->tab[0])
		{
			if (s->count_pipes && s->here_doc_open)
				close(s->here_doc[0]);
			free_all(s, 0);
		}
		if (s->tab[0])
			exec_path(s, ft_is_buildin(s->tab[0]), 1);
	}
	else
		return (do_parent(s));
	return (SUCCESS);
}
