/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thole <thole@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 12:54:07 by thole             #+#    #+#             */
/*   Updated: 2024/02/04 12:54:09 by thole            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	g_sig;

int	wait_pid(t_struct *s)
{
	int	ret;

	ret = 0;
	s->nl = 0;
	while (1)
	{
		if (val_wait(s, &ret) == BREAK)
			break ;
	}
	g_sig = 0;
	return (ret);
}

int	is_token(int token)
{
	if (token == TK_AND || token == TK_OR || token == TK_DLMTR
		|| token == TK_SINGLE || token == TK_PIPES || token == TK_PRIO
		|| token == TK_END_PRIO || token == TK_APPEND || token == TK_ARG
		|| token == TK_AND || token == TK_AND || token == TK_WILD
		|| token == TK_DOUBLE || token == TK_OUTPUT || token == TK_INPUT
		|| token == TK_EXPAND || token == TK_ENV_VAR)
		return (1);
	return (0);
}

int	parsing(t_struct *s)
{
	if (quote_checker(s->str) < SUCCESS)
		return (printf("%s", ERR_QUOTES), free(s->str), CONTINUE);
	if (check_parenthesis(s->str) == ERR_PARS)
		return (printf("%s", ERR_PTSES), free(s->str), CONTINUE);
	if (ft_prototype_list(s) == ERR_MALLOC)
		return (ft_dprintf(2, "Malloc\n"), free(s->str), s->exit_val = -2,
			CONTINUE);
	s->head_parse = s->p_lst;
	if (ft_change_list(s) == ERR_MALLOC)
		return (ft_dprintf(2, "Malloc\n"), free(s->str), s->exit_val = -2,
			CONTINUE);
	init_heads_free(s);
	return (parser_args(s));
}

int	minishell(t_struct *s, char *str)
{
	while (1)
	{
		init_minishell(s);
		sig_init(s);
		str = readline(PROMPT);
		if (!str)
			ctr_d_exit(s);
		reset_signal(s);
		s->str = ft_strdup(str);
		free(str);
		if (!s->str)
		{
			ft_dprintf(2, "Malloc\n");
			s->exit_val = -2;
			continue ;
		}
		add_history((const char *)s->str);
		if (parsing(s) == BREAK)
			break ;
		else
			continue ;
	}
	return (s->exit_val);
}

int	main(int argc, char **argv, char **env)
{
	t_struct	s;
	char		*str;

	g_sig = 0;
	str = NULL;
	if (isatty(STDIN_FILENO) == 0)
		return (ft_dprintf(STDERR_FILENO, "Wrong STDIN\n"), EXIT_FAILURE);
	(void)argv;
	(void)argc;
	s.exit_arg = 0;
	s.string_error = NULL;
	s.error_cd = 0;
	s.i_n_quotes = 0;
	if (init_env(&s, env) == ERR_MALLOC)
		return (ERR_MALLOC);
	set_val(&s, 0);
	return (minishell(&s, str));
}
