/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thole <thole@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 14:43:19 by thole             #+#    #+#             */
/*   Updated: 2024/03/02 14:43:20 by thole            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	token_redirection(int token, int mode)
{
	if (mode == 0)
	{
		if (token == TK_APPEND || token == TK_DLMTR || token == TK_OUTPUT
			|| token == TK_INPUT)
			return (1);
	}
	else if (mode == 1)
	{
		if (token == TK_APPEND || token == TK_OUTPUT)
			return (1);
		else if (token == TK_DLMTR || token == TK_INPUT)
			return (2);
	}
	else if (mode == 3)
	{
		if (token == TK_APPEND || token == TK_DLMTR || token == TK_OUTPUT
			|| token == TK_INPUT || token == TK_PIPES || token == TK_PRIO
			|| token == TK_AND || token == TK_OR)
			return (1);
	}
	return (0);
}

int	fill_cmd_tab(t_tokens **list, t_struct **s)
{
	int	i;

	i = 0;
	while ((*s)->tab[i])
		i++;
	if ((*list)->token == TK_END)
		return ((*s)->tab[i] = NULL, SUCCESS);
	while ((*list)->next)
	{
		if (token_redirection((*list)->token, 3))
			break ;
		if ((*list)->str)
		{
			if (epur_str((*list)->str, s, &i) != SUCCESS)
				return (ERR_MALLOC);
		}
		i++;
		(*list) = (*list)->next;
	}
	(*s)->tab[i] = NULL;
	return (SUCCESS);
}

/*here, this one,if it's exit the exit variable should be set to EXIT,
	that's the only thing you need to worry about,
	also stat is kinda useless but it's because i don't get
	how the export and stuff with pipes and && and || work,
	so feel free to use it or not,
	and if stat is at 1,it means that we're inside a && or a
		|| so you shouldn't pipe
*/
int	do_exec(t_struct **s, t_file *file, int stat)
{
	if ((*s)->tab[0] && check_buildin(*s) == 0 && (*s)->count_pipes == 0)
		return (execute_buildin_normal(*s));
	stat = exec(*s, file);
	(*s)->is_first = 0;
	(*s)->counter++;
	if (stat != SUCCESS)
		return (stat);
	return (SUCCESS);
}

int	prep_to_send_to_exec(t_struct *s, t_tokens *list, t_file *file, int depth)
{
	int	status;

	status = 0;
	epur_commands(&s, file, 0);
	s->file = file;
	s->is_pipe = 1;
	if (list->token == TK_END)
	{
		s->end = 1;
		s->is_last = 1;
	}
	status = do_exec(&s, file, 0);
	if (status != SUCCESS)
		return (flush_files(file, s), flush_array(s->tab), status);
	flush_files(file, s);
	flush_array(s->tab);
	if (list->token == TK_END && s->exit == EXIT && depth == 0)
		return (EXIT);
	return (SUCCESS);
}

/*function to fill the file struct and command tab,
	you have to check the s->tab for the commands and
		the file struct passed as parameters,
	even if there is no command, the files should be opened,
		just fill the do_exec function*/
int	execute(t_struct *s, t_tokens *list, int depth, int pipe)
{
	t_file	file;
	int		status;

	set_files(&file);
	s->end = 0;
	(void)pipe;
	while (list->next)
	{
		if (is_arg(list->token) || token_redirection(list->token, 0))
		{
			status = recursive_filler(&s, &list, &file);
			if (status != SUCCESS)
				return (status);
		}
		if (list->token == TK_PIPES || list->token == TK_END)
		{
			status = prep_to_send_to_exec(s, &(*list), &file, depth);
			if (status != SUCCESS)
				return (status);
		}
		if (list->next)
			list = list->next;
	}
	return (SUCCESS);
}
