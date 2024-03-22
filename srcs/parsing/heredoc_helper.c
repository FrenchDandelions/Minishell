/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_helper.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thole <thole@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 17:25:41 by thole             #+#    #+#             */
/*   Updated: 2024/03/22 17:25:43 by thole            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	check_str(char **str)
{
	if (!(*str)[0])
	{
		free(*str);
		*str = ft_strdup("\n");
		if (!(*str))
			return (ERR_MALLOC);
	}
	return (SUCCESS);
}

int	ret_n_print(char *lim, char *buf, char *str, t_tokens **list)
{
	return (ft_dprintf(STDERR_FILENO, "%s%s%s')\n\033[0m", ERR_MINI_DOC,
			ERR_MINI_DOC2, lim), end_heredoc(&(*list), buf, str));
	return (SUCCESS);
}

int	add_to_buffer(char **buf, char *str)
{
	if ((*buf))
	{
		(*buf) = ft_gnl_strjoin((*buf), str, (int)ft_strlen(str));
		if (!(*buf))
			return (ERR_MALLOC);
	}
	else
	{
		(*buf) = ft_strdup(str);
		if (!(*buf))
			return (free(str), ERR_MALLOC);
	}
	return (SUCCESS);
}

int	check_heredoc(t_tokens **list)
{
	int		err;
	char	*dup;

	if ((*list)->token == TK_DLMTR)
	{
		if (!(*list)->next && (*list)->token == TK_DLMTR)
			return (ERR_PARS);
		else if ((*list)->next && ((*list)->next->token == TK_ARG
				|| (*list)->next->token == TK_DOUBLE
				|| (*list)->next->token == TK_SINGLE)
			&& (*list)->token == TK_DLMTR)
		{
			dup = ft_strdup((*list)->next->str);
			if (!dup)
				return (ERR_MALLOC);
			dup = takeoff_quotes(dup);
			if (!dup)
				return (ERR_MALLOC);
			err = open_heredoc(&(*list), dup);
			ft_memdel(dup);
			(*list) = (*list)->next;
			return (err);
		}
	}
	return (SUCCESS);
}

int	parse_heredoc(t_struct *s)
{
	t_tokens	*temp;
	int			err;

	(void)s;
	temp = s->head_ll;
	while (temp->next)
	{
		err = check_heredoc(&temp);
		if (err == ERR_PARS)
			return (print_error("<<"));
		else if (err == ERR_MALLOC)
			return (ERR_MALLOC);
		else if (err == QUIT)
			return (QUIT);
		temp = temp->next;
	}
	return (SUCCESS);
}
