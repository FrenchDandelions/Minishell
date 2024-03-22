/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_errors.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thole <thole@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 12:54:12 by thole             #+#    #+#             */
/*   Updated: 2024/02/23 12:54:13 by thole            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	is_pipe(int token, int i)
{
	if (i == 1 && (token == TK_PIPES || token == TK_AND))
		return (1);
	else if (i == 0 && (token == TK_PIPES || token == TK_AND || token == TK_OR))
		return (1);
	else if (i == 2 && (token == TK_ARG || token == TK_SINGLE
			|| token == TK_DOUBLE))
		return (1);
	else if (i == 3 && token == TK_PRIO)
		return (1);
	else if (i == 4 && token == TK_END_PRIO)
		return (1);
	return (0);
}

static int	is_redirection(int token, int i)
{
	if (i == 0)
	{
		if (token == TK_INPUT || token == TK_APPEND || token == TK_DLMTR
			|| token == TK_OUTPUT || token == TK_AND || token == TEMP_AND)
			return (1);
	}
	else if (i == 2)
	{
		if (token == TK_INPUT || token == TK_APPEND || token == TK_DLMTR
			|| token == TK_OUTPUT)
			return (1);
	}
	else
	{
		if (token == TK_INPUT || token == TK_APPEND || token == TK_DLMTR
			|| token == TK_OUTPUT || token == TK_AND || token == TEMP_AND
			|| token == TK_PIPES || token == TK_OR)
			return (1);
	}
	return (0);
}

static int	is_special(int token)
{
	if (token == TK_INPUT || token == TK_APPEND || token == TK_DLMTR
		|| token == TK_OUTPUT || token == TK_AND || token == TEMP_AND
		|| token == TK_PIPES || token == TK_AND)
		return (1);
	return (0);
}

int	parser_part_two(t_tokens *temp)
{
	if (temp->next && is_pipe(temp->token, 1) && is_pipe(temp->next->token, 1))
		return (print_error(temp->next->str));
	else if (temp->next && is_pipe(temp->token, 3) && is_pipe(temp->next->token,
			4))
		return (print_error(temp->next->str));
	else if (temp->next && temp->token == TK_END_PRIO
		&& is_redirection(temp->next->token, 2))
		return (print_error(temp->str));
	return (SUCCESS);
}

int	parser(t_struct *s)
{
	t_tokens	*temp;

	temp = s->head_ll;
	while (temp->next)
	{
		if (!temp->prev && is_pipe(temp->token, 0))
			return (print_error(temp->str));
		else if (is_forbidden(temp->token))
			return (print_error2(temp->str));
		else if (temp->prev && (is_pipe(temp->prev->token, 2)
				&& temp->token == TK_PRIO))
			return (print_error(temp->str));
		else if (temp->next->token == TK_END && is_special(temp->token))
			return (print_error(NULL));
		else if (temp->next && is_redirection(temp->token, 0)
			&& is_redirection(temp->next->token, 1))
			return (print_error(temp->next->str));
		else if (parser_part_two(&(*temp)) == ERR_PARS)
			return (ERR_PARS);
		temp = temp->next;
	}
	return (SUCCESS);
}
