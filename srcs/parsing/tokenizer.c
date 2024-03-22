/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   norm.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thole <thole@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 13:33:28 by thole             #+#    #+#             */
/*   Updated: 2024/02/18 13:33:29 by thole            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	last_part(t_tokens **list, t_struct **parse, t_tokens **head)
{
	if ((*list)->token != TK_END)
	{
		(*list)->next = new_list();
		if (!(*list)->next)
			return (ERR_MALLOC);
		(*list)->next->prev = (*list);
		(*list)->next->str = NULL;
		(*list) = (*list)->next;
		(*list)->token = (*parse)->p_lst->token;
	}
	(*list)->next = NULL;
	if ((*list)->str)
	{
		free((*list)->str);
		(*list)->str = NULL;
	}
	(*list) = (*head);
	(*parse)->l_lst = (*list);
	return (SUCCESS);
}

int	do_quotes(t_struct **parse, t_tokens **list, t_parse_list **copy, int *size)
{
	int	type;

	(*size) = 0;
	type = (*parse)->p_lst->token;
	(*copy) = (*parse)->p_lst;
	recursive_line_size(&(*parse), &type, &(*size));
	(*parse)->p_lst = (*copy);
	if ((*parse)->p_lst->prev && check_argument((*parse)->p_lst->prev->token))
	{
		(*list)->token = -100;
		while ((*parse)->p_lst->prev
			&& check_argument((*parse)->p_lst->prev->token))
		{
			(*parse)->p_lst = (*parse)->p_lst->prev;
			(*size)++;
		}
	}
	if (quote_line_fill(&(*parse), &(*list), type, &(*size)) == ERR_MALLOC)
		return (ERR_MALLOC);
	return (SUCCESS);
}

int	do_next_stop_token(t_struct **parse, t_tokens **list)
{
	if ((*parse)->p_lst && next_stop_token((*parse)->p_lst->token))
	{
		if (step(&(*list)) == ERR_MALLOC)
			return (ERR_MALLOC);
		(*list)->str = ft_calloc(sizeof(char), 3);
		if (!(*list)->str)
			return (ERR_MALLOC);
		(*list)->token = get_token(&(*parse), &(*list));
	}
	return (SUCCESS);
}

int	string_maker(t_struct **parse, t_tokens **list, t_parse_list **copy)
{
	int	size;

	while ((*parse)->p_lst && (*parse)->p_lst->next)
	{
		size = 0;
		if ((*parse)->p_lst->next)
			(*parse)->p_lst = skip_first((*parse)->p_lst);
		*copy = (*parse)->p_lst;
		get_size(&(*parse), &(*list), &size);
		if ((*parse)->p_lst)
		{
			if ((check_which_argument(&(*parse), &(*list), &(*copy),
						&size)) == ERR_MALLOC)
				return (ERR_MALLOC);
		}
		if ((*parse)->p_lst && !(*parse)->p_lst->next)
			break ;
	}
	return (SUCCESS);
}

int	ft_change_list(t_struct *parse)
{
	t_tokens		*list;
	t_tokens		*head;
	t_parse_list	*copy;

	head = new_list();
	if (!head)
		return (ERR_MALLOC);
	list = head;
	copy = parse->p_lst;
	if ((string_maker(&parse, &list, &copy) == ERR_MALLOC))
		return (ft_free_changed_list(head), ERR_MALLOC);
	if (last_part(&(list), &(parse), &(head)) == ERR_MALLOC)
		return (ft_free_changed_list(head), ERR_MALLOC);
	return (SUCCESS);
}
