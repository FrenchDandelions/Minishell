/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_and_parenthesis.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thole <thole@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 16:20:12 by thole             #+#    #+#             */
/*   Updated: 2024/03/20 16:20:13 by thole            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	quote_checker(char *str)
{
	int		i;
	char	type;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			type = str[i];
			i++;
			while (str[i] && str[i] != type)
				i++;
		}
		if (!str[i] && type == '\'')
			return (ERR_SINGLE);
		else if (!str[i] && type == '\"')
			return (ERR_DOUBLE);
		i++;
	}
	return (SUCCESS);
}

int	check_parenthesis(char *str)
{
	int		i;
	int		nb;
	char	type;

	i = 0;
	nb = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			type = str[i];
			i++;
			while (str[i] && str[i] != type)
				i++;
		}
		if (str[i] == '(')
			nb++;
		else if (str[i] == ')')
			nb--;
		i++;
	}
	if (nb != 0)
		return (ERR_PARS);
	return (SUCCESS);
}

int	check_list(t_tokens *list)
{
	t_tokens	*temp;
	int			i;

	temp = list;
	i = 0;
	while (temp->next)
	{
		if (is_token(temp->token))
			i++;
		temp = temp->next;
	}
	return (i);
}
