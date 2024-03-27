/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thole <thole@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 17:28:04 by thole             #+#    #+#             */
/*   Updated: 2024/03/20 17:28:05 by thole            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

int	longlonglen(long long int n)
{
	int				i;
	long long int	num;

	i = 0;
	num = n;
	if (num < 0)
		i++;
	while (num)
	{
		i++;
		num /= 10;
	}
	return (i);
}

int	ft_strlen_ps(char *s, int i, int j)
{
	if (s[i] == '-')
		i++;
	while (s[i + j])
	{
		if ((s[i + j] == '0' && s[0] == '-' && i == 1) || (s[i + j] == '0'
				&& i == 0))
		{
			while (s[i + j] == '0')
				j++;
			if (!s[i + j])
			{
				i--;
				break ;
			}
		}
		if (s[i + j])
			i++;
	}
	if (s[0] == '+')
		i--;
	return (i);
}

int	is_only_num(char *s)
{
	int	i;

	i = 0;
	if (s[i] == '-' || s[i] == '+')
		i++;
	while (s[i])
	{
		if (!ft_isdigit(s[i]))
			return (0);
		i++;
	}
	return (1);
}
