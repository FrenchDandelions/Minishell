/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flush_and-epur.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thole <thole@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 16:43:48 by thole             #+#    #+#             */
/*   Updated: 2024/03/22 16:43:49 by thole            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	flush_array(char **tab)
{
	int	i;

	i = 0;
	while (tab && tab[i])
	{
		free(tab[i]);
		tab[i] = NULL;
		i++;
	}
	if (tab)
		free(tab);
	tab = NULL;
}

int	epur_files(t_file *f, t_struct **s, int i)
{
	char	*dup;

	if (f->files[i] && f->modes[i] != TK_DLMTR)
	{
		dup = takeoff_quotes(expand(f->files[i], (*s)->env, *s));
		if (!dup)
			return (ERR_MALLOC);
		f->files[i] = dup;
	}
	else if (f->files[i] && f->modes[i] == TK_DLMTR)
	{
		if (f->token[i] == TK_DOUBLE || f->token[i] == TK_SINGLE)
			dup = ft_strdup(f->files[i]);
		else
			dup = expand_heredoc(f->files[i], (*s)->env, *s);
		if (!dup)
			return (ERR_MALLOC);
		f->files[i] = dup;
	}
	if (f->files[i] && f->files[i + 1])
		return (epur_files(f, s, i + 1));
	return (SUCCESS);
}

void	set_files(t_file *file)
{
	file->files = NULL;
	file->modes = NULL;
	file->token = NULL;
}

void	flush_files(t_file *file, t_struct *s)
{
	int	i;

	i = 0;
	while (file->files && file->files[i] != NULL)
	{
		free(file->files[i]);
		file->files[i] = NULL;
		file->modes[i] = NOTHING;
		file->token[i] = NOTHING;
		i++;
	}
	if (file->files)
		free(file->files);
	if (file->token)
		free(file->token);
	if (file->modes)
		free(file->modes);
	s->infile = NULL;
	s->outfile = NULL;
	s->mode_in = NOTHING;
	s->mode_out = NOTHING;
	s->token_in = NOTHING;
	s->token_out = NOTHING;
	set_files(file);
}
