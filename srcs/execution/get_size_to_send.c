/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_size_to_send.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thole <thole@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 16:47:58 by thole             #+#    #+#             */
/*   Updated: 2024/03/22 16:48:00 by thole            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	recursive_tab_filler(t_struct **s, t_tokens **list, t_file *file)
{
	if (fill_cmd_tab(&(*list), &(*s)) == ERR_MALLOC)
		return (flush_files(file, *s), ERR_MALLOC);
	if (token_redirection((*list)->token, 0))
	{
		while ((*list)->next && (*list)->next->str
			&& token_redirection((*list)->token, 0))
		{
			if (create_new_file(file, (*list)->next->str, (*list)->token,
					(*list)->next->token) == ERR_MALLOC)
				return (flush_array((*s)->tab), flush_files(file, *s),
					ERR_MALLOC);
			(*list) = (*list)->next->next;
		}
	}
	if (is_arg((*list)->token))
		return (recursive_tab_filler(&(*s), &(*list), file));
	return (SUCCESS);
}

void	get_size_files(t_tokens **list, int *size_files)
{
	while ((*list)->next && (*list)->next->str
		&& token_redirection((*list)->token, 0))
	{
		(*size_files)++;
		(*list) = (*list)->next->next;
	}
}

int	get_size_tab(t_tokens *list, int *size_tab, int *size_files)
{
	if (list->token == TK_END)
		return (SUCCESS);
	while (list->next)
	{
		if (token_redirection(list->token, 0))
			get_size_files(&list, &(*size_files));
		if (list->token == TK_END || list->token == TK_PIPES)
			break ;
		if (list->str)
			(*size_tab)++;
		list = list->next;
	}
	return (SUCCESS);
}

int	recursive_filler(t_struct **s, t_tokens **list, t_file *file)
{
	int	size_tab;
	int	size_files;

	size_tab = 0;
	size_files = 0;
	get_size_tab((*list), &size_tab, &size_files);
	file->files = malloc(sizeof(char *) * (size_files + 1));
	if (!file->files)
		return (ERR_MALLOC);
	file->modes = malloc(sizeof(int) * (size_files + 1));
	if (!file->modes)
		return (free(file->files), ERR_MALLOC);
	file->token = malloc(sizeof(int) * (size_files + 1));
	if (!file->token)
		return (free(file->files), free(file->modes), ERR_MALLOC);
	(*s)->tab = malloc(sizeof(char *) * (size_tab + 1));
	if (!(*s)->tab)
		return (free(file->files), free(file->modes), free(file->token),
			ERR_MALLOC);
	(*s)->tab[0] = NULL;
	file->files[0] = NULL;
	file->modes[0] = NOTHING;
	file->token[0] = NOTHING;
	return (recursive_tab_filler(&(*s), &(*list), &(*file)));
}
