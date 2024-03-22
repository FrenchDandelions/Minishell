/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thole <thole@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 16:44:02 by thole             #+#    #+#             */
/*   Updated: 2024/03/20 16:44:06 by thole            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

extern int	g_sig;

void	ctr_d_exit(t_struct *s)
{
	rl_clear_history();
	free_env(s->env);
	free_env(s->dup_env);
	ft_dprintf(2, "\033[1;95mexit\n\033[0m");
	if (g_sig == 130)
		s->exit_val = 130;
	else if (g_sig == 131)
		s->exit_val = 131;
	exit(s->exit_val);
}

void	free_when_exit(t_struct *s)
{
	ft_free_changed_list(s->l_lst);
	free(s->str);
	rl_clear_history();
	free_env(s->env);
	free_env(s->dup_env);
	if (s->exit_arg && !s->bad_exit)
		exit(s->exit_arg);
	if (!s->bad_exit)
		exit(s->exit_val);
}
