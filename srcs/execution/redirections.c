/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thole <thole@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 16:40:45 by thole             #+#    #+#             */
/*   Updated: 2024/03/22 16:40:47 by thole            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	try_dups(t_file *f, t_struct *s)
{
	(void)f;
	if (!s->is_first && s->count_pipes)
	{
		dup2(s->last_fd, STDIN_FILENO);
		close(s->last_fd);
	}
	if (s->count_pipes != s->counter && s->count_pipes)
	{
		dup2(s->pipe[1], STDOUT_FILENO);
		close(s->pipe[1]);
		close(s->pipe[0]);
	}
}

void	try_redirections(t_file *f, t_struct *s)
{
	(void)f;
	if (s->outfile)
	{
		s->fd_out = open_struct_file(s->outfile, s->mode_out, s);
		dup2(s->fd_out, STDOUT_FILENO);
		close(s->fd_out);
		free(s->outfile);
		s->outfile = NULL;
	}
	if ((s->infile || s->here_doc_open))
	{
		s->fd_in = open_struct_file(s->infile, s->mode_in, s);
		dup2(s->fd_in, STDIN_FILENO);
		close(s->fd_in);
		if (s->infile)
		{
			free(s->infile);
			s->infile = NULL;
		}
	}
}

int	open_out(t_file *f, t_struct *s, int i)
{
	int	status;

	if (f->modes[i] == TK_APPEND)
	{
		status = open_append(f->files[i], f->token[i], s);
		if (status)
			return (status);
	}
	else if (f->modes[i] == TK_OUTPUT)
	{
		status = open_output(f->files[i], f->token[i], s);
		if (status)
			return (status);
	}
	return (0);
}

int	open_in(t_file *f, t_struct *s, int i)
{
	int	status;

	if (f->modes[i] == TK_INPUT)
	{
		status = open_input(f->files[i], f->token[i], s);
		if (status)
			return (status);
	}
	else if (f->modes[i] == TK_DLMTR)
	{
		status = open_dlmtr(f->files[i], f->token[i], s);
		if (status)
			return (status);
	}
	return (0);
}

int	open_files(t_file *f, t_struct *s)
{
	int	i;
	int	status;

	i = 0;
	status = 0;
	while (f->files[i])
	{
		if (f->modes[i] == TK_APPEND || f->modes[i] == TK_OUTPUT)
		{
			status = open_out(f, s, i);
			if (status)
				return (status);
		}
		else if (f->modes[i] == TK_INPUT || f->modes[i] == TK_DLMTR)
		{
			status = open_in(f, s, i);
			if (status)
				return (status);
		}
		i++;
	}
	return (0);
}
