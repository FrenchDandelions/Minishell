/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thole <thole@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 17:27:35 by thole             #+#    #+#             */
/*   Updated: 2024/03/20 17:27:37 by thole            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

void	get_err_string(t_struct *s, int len)
{
	char	*str;
	int		i;

	str = ft_calloc(sizeof(char), len);
	if (!str)
		free_all(s, -2);
	i = 0;
	while (i < len - 1)
	{
		str[i] = s->tab[1][i];
		i++;
	}
	str[i] = '\0';
	s->string_error = str;
}

void	set_error(t_struct *s)
{
	int	len;

	len = (int)(ft_strlen(s->tab[1]) + 1);
	s->exit_arg = 2;
	s->num_err_exit = 1;
	get_err_string(s, len);
}

void	set_val(t_struct *s, int i)
{
	s->bad_exit = i;
	s->exit_val = i;
}

void	ft_exit(t_struct *s)
{
	long long int	stat;

	s->exit = EXIT;
	if (s->count_pipes)
		free_all(s, 0);
	if (s->tab[1])
	{
		stat = ft_atoll(s->tab[1]);
		if ((longlonglen(stat) != ft_strlen_ps(s->tab[1], 0, 0))
			|| !is_only_num(s->tab[1]))
			set_error(s);
		else
		{
			if (s->tab[2])
				set_val(s, 1);
			else if (stat < 0 || stat > 256)
				s->exit_arg = stat % 256;
			else
				s->exit_arg = stat;
		}
	}
}
