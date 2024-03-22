/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_struct.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thole <thole@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 16:36:45 by thole             #+#    #+#             */
/*   Updated: 2024/03/20 16:36:47 by thole            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	init_heads_free(t_struct *s)
{
	s->head_ll = s->l_lst;
	s->p_lst = s->head_parse;
	s->temp = s->head_ll;
	ft_free_parse_list(s->p_lst);
}

void	init_args(t_struct *s)
{
	s->tab = NULL;
	s->infile = NULL;
	s->outfile = NULL;
	s->mode_in = NOTHING;
	s->mode_out = NOTHING;
	s->token_in = NOTHING;
	s->token_out = NOTHING;
	s->count_pipes = 0;
	s->counter = 0;
	s->here_doc_open = 0;
}

void	init_minishell(t_struct *s)
{
	s->exit = 0;
	s->exported = 0;
	s->unsetted = 0;
	s->bad_exit = 0;
	s->is_first = 1;
	s->is_last = 0;
	s->num_err_exit = 0;
}
