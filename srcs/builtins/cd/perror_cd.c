/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perror_cd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thole <thole@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 17:23:28 by thole             #+#    #+#             */
/*   Updated: 2024/03/20 17:23:30 by thole            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

int	print_error_cd(t_struct *s)
{
	ft_dprintf(STDERR_FILENO, "Minishell: cd: too many arguments\n");
	if (s->count_pipes)
		free_all(s, 1);
	s->exit_val = 1;
	return (1);
}

void	perror_cd(char *s)
{
	ft_dprintf(STDERR_FILENO, "Minishell: cd: ");
	perror(s);
}

int	free_error_cd(t_struct *s, char *home)
{
	if (home)
	{
		perror_cd(home);
		free(home);
	}
	else
		perror_cd(s->tab[1]);
	if (s->count_pipes)
		free_all(s, 1);
	s->exit_val = 1;
	return (1);
}

int	free_cd(t_struct *s, char *home)
{
	if (home)
		free(home);
	if (s->count_pipes)
		free_all(s, 0);
	if (!s->error_cd)
		s->exit_val = 0;
	s->error_cd = 0;
	return (0);
}

int	err_home(t_struct *s, char *home)
{
	return (ft_dprintf(STDERR_FILENO, "Minishell: cd: HOME not set\n"),
		free(home), free_all(s, 1), 1);
}
