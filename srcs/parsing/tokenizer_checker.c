/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_checker.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thole <thole@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 17:37:40 by thole             #+#    #+#             */
/*   Updated: 2024/03/22 17:37:41 by thole            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	check_which_argument(t_struct **parse, t_tokens **list, t_parse_list **copy,
		int *size)
{
	if (create(&(*list), &(*size)) == ERR_MALLOC)
		return (ERR_MALLOC);
	(*parse)->p_lst = (*copy);
	if ((*parse)->p_lst->next)
		(*parse)->p_lst = skip_first((*parse)->p_lst);
	if ((create_till_next_arg(&(*parse), &(*list), &(*size))) == ERR_MALLOC)
		return (ERR_MALLOC);
	if ((*parse)->p_lst->token == TK_SINGLE
		|| (*parse)->p_lst->token == TK_DOUBLE)
	{
		if ((do_quotes(&(*parse), &(*list), &(*copy), &(*size))) == ERR_MALLOC)
			return (ERR_MALLOC);
	}
	if ((*parse)->p_lst)
		(*parse)->p_lst = skip_first((*parse)->p_lst);
	if ((do_next_stop_token(&(*parse), &(*list))) == ERR_MALLOC)
		return (ERR_MALLOC);
	if ((*parse)->p_lst)
		(*parse)->p_lst = skip_first((*parse)->p_lst);
	return (SUCCESS);
}

int	check_if_arg(t_struct *parse)
{
	if (parse->p_lst->next && (parse->p_lst->token == TK_ARG
			|| parse->p_lst->token == TK_WILD)
		&& parse->p_lst->token != TK_SKIP)
		return (1);
	return (0);
}

int	check_argument(int token)
{
	if ((token == TK_ARG || token == TK_WILD) && token != TK_SKIP
		&& token != TK_END)
		return (1);
	return (0);
}

int	next_stop_token(int token)
{
	if ((token == TK_PIPES || token == TK_APPEND || token == TK_DLMTR
			|| token == TK_INPUT || token == TK_OUTPUT || token == TK_END
			|| token == TK_END_PRIO || token == TK_PRIO || token == TK_AND
			|| token == TEMP_AND || token == TK_OR))
		return (1);
	return (0);
}

t_parse_list	*skip_first(t_parse_list *copy)
{
	while (copy->next && copy->token == TK_SKIP)
	{
		copy = copy->next;
	}
	return (copy);
}
