/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_getter.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thole <thole@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 17:35:02 by thole             #+#    #+#             */
/*   Updated: 2024/03/22 17:35:03 by thole            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	get_size(t_struct **parse, t_tokens **list, int *size)
{
	while (check_if_arg((*parse))
		&& (!(next_stop_token((*parse)->p_lst->token))))
	{
		(*size)++;
		if ((*list)->token != TK_SINGLE && (*list)->token != TK_DOUBLE
			&& ((*parse)->p_lst->token == TK_SINGLE
				|| (*parse)->p_lst->token == TK_DOUBLE) && !(*list)->str)
			(*list)->token = (*parse)->p_lst->token;
		else if ((*list)->token == -100)
			(*list)->token = (*parse)->p_lst->token;
		(*parse)->p_lst = (*parse)->p_lst->next;
	}
	return (SUCCESS);
}

int	quote_line_fill(t_struct **parse, t_tokens **list, int type, int *size)
{
	int	delimiter;

	delimiter = *size;
	(*size)++;
	if (create(&(*list), &(*size)) == ERR_MALLOC)
		return (ERR_MALLOC);
	while ((*parse)->p_lst->next && (*size) <= delimiter)
	{
		(*list)->str[(*size)] = (*parse)->p_lst->c;
		if ((*list)->token == -100)
			(*list)->token = type;
		(*size)++;
		(*parse)->p_lst = (*parse)->p_lst->next;
	}
	return (SUCCESS);
}

void	size_until_nothing_or_special_char(t_struct **parse, int *type,
		int *size)
{
	while ((*parse)->p_lst->next && (*parse)->p_lst->token != TK_END
		&& (*parse)->p_lst->token != (*type))
	{
		(*size)++;
		(*parse)->p_lst = (*parse)->p_lst->next;
	}
	if ((*parse)->p_lst->next)
	{
		(*size)++;
		((*parse)->p_lst = (*parse)->p_lst->next);
	}
	while ((*parse)->p_lst->next && (*parse)->p_lst->token != TK_END
		&& check_argument((*parse)->p_lst->token))
	{
		(*size)++;
		(*parse)->p_lst = (*parse)->p_lst->next;
	}
	if (check_argument((*parse)->p_lst->token))
		(*size)++;
}

int	recursive_line_size(t_struct **parse, int *type, int *size)
{
	if ((*parse)->p_lst->token == TK_SINGLE
		|| (*parse)->p_lst->token == TK_DOUBLE)
		(*type) = (*parse)->p_lst->token;
	(*parse)->p_lst = (*parse)->p_lst->next;
	(*size)++;
	if ((*parse)->p_lst->token == (*type))
	{
		(*parse)->p_lst = (*parse)->p_lst->next;
		while ((*parse)->p_lst->next && (*parse)->p_lst->token != TK_END
			&& check_argument((*parse)->p_lst->token))
		{
			(*size)++;
			(*parse)->p_lst = (*parse)->p_lst->next;
		}
		(*size)++;
	}
	else
		size_until_nothing_or_special_char(&(*parse), &(*type), &(*size));
	if ((*parse)->p_lst->next && ((*parse)->p_lst->token == TK_DOUBLE
			|| (*parse)->p_lst->token == TK_SINGLE))
		return (recursive_line_size(&(*parse), &(*type), &(*size)));
	if (!check_argument((*parse)->p_lst->token))
		(*size)--;
	return (SUCCESS);
}

int	get_token(t_struct **parse, t_tokens **list)
{
	int	token;

	if ((*parse)->p_lst->token != TK_APPEND
		&& (*parse)->p_lst->token != TK_DLMTR
		&& (*parse)->p_lst->token != TK_EXPAND
		&& (*parse)->p_lst->token != TK_AND && (*parse)->p_lst->token != TK_OR)
	{
		token = (*parse)->p_lst->token;
		(*list)->str[0] = (*parse)->p_lst->c;
		(*list)->str[1] = '\0';
		if ((*parse)->p_lst->next)
			(*parse)->p_lst = (*parse)->p_lst->next;
		return (token);
	}
	token = (*parse)->p_lst->token;
	(*list)->str[0] = (*parse)->p_lst->c;
	(*parse)->p_lst = (*parse)->p_lst->next;
	(*list)->str[1] = (*parse)->p_lst->c;
	(*parse)->p_lst = (*parse)->p_lst->next;
	(*list)->str[2] = '\0';
	return (token);
}
