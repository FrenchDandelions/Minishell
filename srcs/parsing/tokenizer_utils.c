/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thole <thole@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 17:35:13 by thole             #+#    #+#             */
/*   Updated: 2024/03/22 17:35:14 by thole            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_tokens	*new_node(int size)
{
	t_tokens	*list;

	(void)size;
	list = malloc(sizeof(t_tokens));
	if (!list)
		return (NULL);
	list->next = NULL;
	list->prev = NULL;
	list->token = -100;
	return (list);
}

t_tokens	*new_list(void)
{
	t_tokens	*list;

	list = malloc(sizeof(t_tokens));
	if (!list)
		return (NULL);
	list->next = NULL;
	list->str = NULL;
	list->prev = NULL;
	list->token = -100;
	return (list);
}

int	step(t_tokens **list)
{
	if ((*list)->token == -100)
	{
		if ((*list)->str)
			free((*list)->str);
		(*list)->str = NULL;
		return (SUCCESS);
	}
	(*list)->next = new_node(0);
	if (!(*list)->next)
		return (ERR_MALLOC);
	(*list)->next->prev = (*list);
	(*list) = (*list)->next;
	(*list)->str = NULL;
	return (SUCCESS);
}

int	create(t_tokens **list, int *size)
{
	if ((*list)->token == -100 || !(*list)->str)
	{
		if ((*list)->str)
			free((*list)->str);
		(*list)->str = ft_calloc(sizeof(char), (*size) + 1);
		if (!(*list)->str)
			return (ERR_MALLOC);
		(*size) = 0;
		return (SUCCESS);
	}
	(*list)->next = new_node(*size);
	if (!(*list)->next)
		return (ERR_MALLOC);
	(*list)->next->prev = (*list);
	(*list) = (*list)->next;
	(*list)->str = ft_calloc(sizeof(char), (*size) + 1);
	if (!(*list)->str)
		return (ERR_MALLOC);
	(*size) = 0;
	return (SUCCESS);
}

int	create_till_next_arg(t_struct **parse, t_tokens **list, int *size)
{
	while (check_if_arg((*parse))
		&& (!(next_stop_token((*parse)->p_lst->token))))
	{
		(*list)->str[(*size)] = (*parse)->p_lst->c;
		if ((*list)->token != TK_SINGLE && (*list)->token != TK_DOUBLE
			&& ((*parse)->p_lst->token == TK_SINGLE
				|| (*parse)->p_lst->token == TK_DOUBLE))
			(*list)->token = (*parse)->p_lst->token;
		else if ((*list)->token == -100)
			(*list)->token = (*parse)->p_lst->token;
		(*size)++;
		(*parse)->p_lst = (*parse)->p_lst->next;
	}
	return (SUCCESS);
}
