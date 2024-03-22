/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup_and_close_normal.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thole <thole@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 20:21:32 by thole             #+#    #+#             */
/*   Updated: 2024/03/22 20:21:33 by thole            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	dup_fds(t_struct *s)
{
	s->save_in = dup(STDIN_FILENO);
	s->save_out = dup(STDOUT_FILENO);
}

void	close_dup_fds(t_struct *s)
{
	dup2(s->save_in, STDIN_FILENO);
	close(s->save_in);
	dup2(s->save_out, STDOUT_FILENO);
	close(s->save_out);
}
