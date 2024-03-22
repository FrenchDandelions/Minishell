/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_helper.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thole <thole@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 16:45:47 by thole             #+#    #+#             */
/*   Updated: 2024/03/22 16:45:49 by thole            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	check_buildin(t_struct *s)
{
	if (ft_strcmp(s->tab[0], "exit") == 0)
		return (0);
	else if (ft_strcmp(s->tab[0], "export") == 0)
		return (0);
	else if (ft_strcmp(s->tab[0], "unset") == 0)
		return (0);
	else if (ft_strcmp(s->tab[0], "cd") == 0)
		return (0);
	return (1);
}

int	execute_buildin_normal(t_struct *s)
{
	if (ft_strcmp(s->tab[0], "exit") == 0)
		return (ft_exit(s), EXIT);
	else if (ft_strcmp(s->tab[0], "export") == 0)
		return (ft_export_notchild(s, s->dup_env), NORMAL);
	else if (ft_strcmp(s->tab[0], "unset") == 0)
		return (ft_unset(s, s->dup_env), NORMAL);
	else if (ft_strcmp(s->tab[0], "cd") == 0)
		return (ft_cd(s), NORMAL);
	return (SUCCESS);
}

int	create_new_file(t_file *f, char *file, int type, int token)
{
	int	i;

	i = 0;
	while (f->files[i])
		i++;
	f->modes[i] = type;
	f->files[i] = file;
	if (!f->files[i])
		return (ERR_MALLOC);
	f->files[i + 1] = NULL;
	f->token[i] = token;
	return (SUCCESS);
}

int	is_arg(int token)
{
	if (token == TK_ARG || token == TK_WILD || token == TK_DOUBLE
		|| token == TK_SINGLE)
		return (1);
	return (0);
}

int	epur_str(char *s1, t_struct **s, int *i)
{
	char	*str;

	str = expand(s1, (*s)->env, *s);
	if (!str)
		return ((*s)->tab[(*i)] = NULL, flush_array((*s)->tab), ERR_MALLOC);
	if (!str[0])
		return (free(str), (*i)--, SUCCESS);
	str = takeoff_quotes(str);
	if (!str)
		return ((*s)->tab[(*i)] = NULL, flush_array((*s)->tab), ERR_MALLOC);
	(*s)->tab[(*i)] = str;
	return (SUCCESS);
}
