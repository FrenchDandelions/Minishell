/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_wait.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thole <thole@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 11:41:52 by thole             #+#    #+#             */
/*   Updated: 2024/03/26 11:41:53 by thole            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

extern int	g_sig;

void	print_nl_wait(t_struct *s)
{
	printf("\n");
	s->nl++;
}

int	val_wait(t_struct *s, int *ret)
{
	int	status;
	int	pid;

	pid = wait(&status);
	if (pid == -1)
		return (BREAK);
	if (WIFSIGNALED(status) && WTERMSIG(status) + 128 == 128 + SIGINT && !s->nl)
		print_nl_wait(s);
	if (pid != s->pid)
		return (CONTINUE);
	if (WIFEXITED(status))
		*ret = WEXITSTATUS(status);
	else
	{
		*ret = 128 + WTERMSIG(status);
		if (*ret == 131)
			ft_dprintf(2, "Quit (core dumped)\n");
		else if (*ret == 130 && !s->nl)
			ft_dprintf(2, "\n");
	}
	return (CONTINUE);
}
