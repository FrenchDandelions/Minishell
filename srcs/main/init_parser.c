/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thole <thole@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 17:27:58 by thole             #+#    #+#             */
/*   Updated: 2024/03/22 17:27:59 by thole            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	err_process_malloc(t_struct *s)
{
	ft_dprintf(2, "Malloc\n");
	ft_free_changed_list(s->l_lst);
	free(s->str);
	s->exit_val = -2;
	return (CONTINUE);
}

int	bad_exit_handler(t_struct *s)
{
	s->num_err_exit = 0;
	if (s->string_error)
	{
		free(s->string_error);
		s->string_error = NULL;
	}
	ft_dprintf(2, "%sMinishell: exit: too many arguments%s\n", PURP, RESET);
	ft_free_changed_list(s->l_lst);
	free(s->str);
	return (CONTINUE);
}

int	process(t_struct *s)
{
	int	stat;

	stat = execute(s, s->head_ll, 0, 0);
	if (stat != EXIT && stat != NORMAL)
		s->exit_val = wait_pid(s);
	if (stat == ERR_PARS)
		return (err_process_malloc(s));
	else if (s->exit == EXIT)
	{
		ft_dprintf(2, "\033[1;95mexit\n\033[0m");
		if (s->bad_exit)
			return (bad_exit_handler(s));
		if (s->num_err_exit)
		{
			ft_dprintf(2, "%s%s%s", ERR_X1, s->string_error, ERR_X2);
			free(s->string_error);
		}
		free_when_exit(s);
	}
	ft_free_changed_list(s->l_lst);
	free(s->str);
	return (SUCCESS);
}

int	handle_err(int err, int err2, t_struct *s)
{
	if (err2 == ERR_MALLOC || err == ERR_MALLOC)
	{
		ft_dprintf(STDERR_FILENO, "ERR_MALLOC");
		ft_free_changed_list(s->l_lst);
		free(s->str);
		s->exit_val = -2;
		return (CONTINUE);
	}
	if (err == ERR_PARS || err2 == ERR_PARS)
	{
		ft_free_changed_list(s->l_lst);
		free(s->str);
		s->exit_val = 2;
		return (CONTINUE);
	}
	if (err2 == QUIT)
	{
		ft_free_changed_list(s->l_lst);
		free(s->str);
		s->exit_val = 130;
		return (CONTINUE);
	}
	return (SUCCESS);
}

int	parser_args(t_struct *s)
{
	int	err;
	int	err2;

	err = parser(s);
	err2 = parse_heredoc(s);
	if (handle_err(err, err2, s) == CONTINUE)
		return (CONTINUE);
	init_args(s);
	if (!check_list(s->head_ll))
	{
		ft_free_changed_list(s->l_lst);
		free(s->str);
		return (CONTINUE);
	}
	count_pipes(s);
	return (process(s));
}
