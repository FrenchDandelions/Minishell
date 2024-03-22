/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_files.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thole <thole@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 14:26:46 by thole             #+#    #+#             */
/*   Updated: 2024/03/09 14:26:48 by thole            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	get_files(t_file *f, t_struct *s)
{
	int	i;

	i = 0;
	while (f->files && f->files[i])
	{
		if (token_redirection(f->modes[i], 1) == 2)
		{
			s->token_in = f->token[i];
			s->mode_in = f->modes[i];
		}
		else if (token_redirection(f->modes[i], 1) == 1)
		{
			s->token_out = f->token[i];
			s->mode_out = f->modes[i];
		}
		i++;
	}
}

int	open_struct_file(char *s, int mode, t_struct *st)
{
	int	fd;

	if (mode == TK_APPEND)
	{
		fd = open(s, O_CREAT | O_APPEND | O_WRONLY, 0644);
		return (fd);
	}
	else if (mode == TK_OUTPUT)
	{
		fd = open(s, O_CREAT | O_TRUNC | O_WRONLY, 0644);
		return (fd);
	}
	else if (mode == TK_INPUT)
	{
		if (st->here_doc_open)
			close(st->here_doc[0]);
		fd = open(s, O_RDONLY, 0644);
		return (fd);
	}
	else if (mode == TK_DLMTR)
	{
		fd = st->here_doc[0];
		return (fd);
	}
	return (SUCCESS);
}

int	do_files(t_file *f, t_struct *s)
{
	if (f->files)
	{
		get_files(f, s);
		s->here_doc_open = 0;
		if (open_files(f, s))
			return (-1);
	}
	try_dups(f, s);
	if (s->tab && s->tab[0])
		try_redirections(f, s);
	else
	{
		if (s->here_doc_open)
			close(s->here_doc[0]);
	}
	return (0);
}
