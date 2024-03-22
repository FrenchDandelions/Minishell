/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thole <thole@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 17:29:42 by thole             #+#    #+#             */
/*   Updated: 2024/03/20 17:29:44 by thole            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

void	ft_env(t_struct *s, char **env, int fake_env)
{
	int	i;

	i = 0;
	(void)env;
	(void)fake_env;
	while (s->env[i])
	{
		printf("%s\n", s->env[i]);
		i++;
	}
	free_all(s, 0);
}
