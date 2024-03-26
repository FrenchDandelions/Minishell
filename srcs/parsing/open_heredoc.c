/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thole <thole@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 17:07:17 by thole             #+#    #+#             */
/*   Updated: 2024/02/27 17:07:18 by thole            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

extern int	g_sig;

int	end_heredoc(t_tokens **list, char *buf, char *str)
{
	free(str);
	free((*list)->next->str);
	if (buf)
	{
		(*list)->next->str = ft_strdup(buf);
		if (!(*list)->next->str)
			return (free(buf), ERR_MALLOC);
		free(buf);
	}
	else
	{
		(*list)->next->str = ft_strdup("");
		if (!(*list)->next->str)
			return (ERR_MALLOC);
	}
	return (SUCCESS);
}

void	heredoc_sig(int code)
{
	(void)code;
	g_sig = 130;
	printf("\n");
	close(STDIN_FILENO);
}

int	handle_close_heredoc(char *buf, char *str, int fd)
{
	if (g_sig == 130)
	{
		if (str)
			free(str);
		if (buf)
			ft_memdel(buf);
		g_sig = 0;
		dup2(fd, STDIN_FILENO);
		close(fd);
		return (QUIT);
	}
	return (SUCCESS);
}

int	join_and_add_to_buffer(char **str, char **buf)
{
	*str = ft_gnl_strjoin(*str, "\n", 1);
	if (!*str && *buf)
		return (free(buf), ERR_MALLOC);
	else if (!*str && !*buf)
		return (ERR_MALLOC);
	if (add_to_buffer(&(*buf), *str) == ERR_MALLOC)
		return (ERR_MALLOC);
	free(*str);
	return (SUCCESS);
}

int	open_heredoc(t_tokens **list, char *lim)
{
	char	*str;
	char	*buf;
	int		fd;

	fd = dup(STDIN_FILENO);
	buf = NULL;
	signal(SIGINT, &heredoc_sig);
	while (1)
	{
		str = readline(PROMPT_HD);
		if (!str || g_sig == 130)
		{
			if (handle_close_heredoc(buf, str, fd) == QUIT)
				return (QUIT);
			return ((close(fd), ret_n_print(lim, buf, str, &(*list))));
		}
		if (check_str(&str) == ERR_MALLOC)
			return (close(fd), ERR_MALLOC);
		if (ft_strcmp(str, lim) == 0)
			return (close(fd), end_heredoc(&(*list), buf, str));
		if (join_and_add_to_buffer(&str, &buf) == ERR_MALLOC)
			return (close(fd), ERR_MALLOC);
	}
	return (0);
}
