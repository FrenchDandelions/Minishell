/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thole <thole@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 14:48:27 by thole             #+#    #+#             */
/*   Updated: 2024/03/09 14:48:28 by thole            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	open_output(char *s, int token, t_struct *st)
{
	char	*str;
	int		fd;

	str = ft_strdup(s);
	if (!str)
		return (ERR_MALLOC);
	if (token != TK_ARG)
	{
		str = takeoff_quotes(str);
		if (!str)
			return (ERR_MALLOC);
	}
	fd = open(str, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == -1)
	{
		perror(str);
		free(str);
		return (ERR_PARS);
	}
	close(fd);
	if (st->outfile)
		free(st->outfile);
	st->outfile = ft_strdup(str);
	free(str);
	return (0);
}

int	open_append(char *s, int token, t_struct *st)
{
	char	*str;
	int		fd;

	str = ft_strdup(s);
	if (!str)
		return (ERR_MALLOC);
	if (token != TK_ARG)
	{
		str = takeoff_quotes(str);
		if (!str)
			return (ERR_MALLOC);
	}
	fd = open(str, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (fd == -1)
	{
		perror(str);
		free(str);
		return (ERR_PARS);
	}
	close(fd);
	if (st->outfile)
		free(st->outfile);
	st->outfile = ft_strdup(str);
	free(str);
	return (0);
}

int	open_input(char *s, int token, t_struct *st)
{
	char	*str;
	int		fd;

	str = ft_strdup(s);
	if (!str)
		return (ERR_MALLOC);
	if (token != TK_ARG)
	{
		str = takeoff_quotes(str);
		if (!str)
			return (ERR_MALLOC);
	}
	fd = open(str, O_RDONLY, 0644);
	if (fd == -1)
	{
		perror(str);
		free(str);
		return (-1);
	}
	close(fd);
	if (st->infile)
		free(st->infile);
	st->infile = ft_strdup(str);
	free(str);
	return (0);
}

int	open_dlmtr(char *s, int token, t_struct *st)
{
	(void)token;
	if (!st->here_doc_open)
	{
		if (pipe(st->here_doc) == -1)
			return (ERR_PIPE);
	}
	else
	{
		close(st->here_doc[0]);
		if (pipe(st->here_doc) == -1)
			return (ERR_PIPE);
	}
	ft_dprintf(st->here_doc[1], "%s", s);
	close(st->here_doc[1]);
	st->here_doc_open++;
	return (0);
}
