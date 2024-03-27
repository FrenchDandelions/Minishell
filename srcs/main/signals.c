/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thole <thole@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 15:57:32 by thole             #+#    #+#             */
/*   Updated: 2024/03/27 14:53:19 by andrew           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

extern int	g_sig;

void	reset_signal(t_struct *s)
{
	if (g_sig == 130)
	{
		s->exit_val = 130;
		g_sig = 0;
	}
}

void	sig_int(int code)
{
	(void)code;
	g_sig = 130;
	printf("\n");
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	handle_child(int code)
{
	if (code == SIGQUIT)
		g_sig = 131;
	else
		g_sig = 130;
}

void	sig_init(t_struct *s)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, &sig_int);
	(void)s;
}

void	sig_child(void)
{
	signal(SIGINT, &handle_child);
	signal(SIGQUIT, &handle_child);
}
