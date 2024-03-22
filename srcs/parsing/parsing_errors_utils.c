/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_errors_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thole <thole@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 17:33:07 by thole             #+#    #+#             */
/*   Updated: 2024/03/22 17:33:08 by thole            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	print_error(char *str)
{
	if (str)
		printf("%sMinishell: syntax error near unexpected token '%s'\n%s", RED,
			str, RESET);
	else
		printf("%sMinishell: syntax error near unexpected token 'newline'\n%s",
			RED, RESET);
	return (ERR_PARS);
}

int	print_error2(char *str)
{
	printf("%sMinishell: forbidden token '%s'\n%s", RED, str, RESET);
	return (ERR_PARS);
}

int	is_forbidden(int token)
{
	if (token == TK_AND || token == TK_OR || token == TK_PRIO
		|| token == TK_END_PRIO)
		return (1);
	return (0);
}
