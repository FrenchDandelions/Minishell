/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thole <thole@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 16:07:05 by thole             #+#    #+#             */
/*   Updated: 2024/03/14 16:07:06 by thole            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_free_parse_list(t_parse_list *list)
{
	t_parse_list	*current;
	t_parse_list	*temp;

	current = list;
	while (current)
	{
		temp = current->next;
		free(current);
		current = temp;
	}
}

void	ft_free_changed_list(t_tokens *list)
{
	t_tokens	*current;
	t_tokens	*temp;

	current = list;
	while (current)
	{
		temp = current->next;
		if (current->str)
			free(current->str);
		free(current);
		current = temp;
	}
}

void	free_stack_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		free(tab[i++]);
}

void	free_env(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		free(env[i]);
		env[i] = NULL;
		i++;
	}
	free(env);
	env = NULL;
}

void	free_all(t_struct *s, int ex)
{
	if (s->tab)
		free_tab(s->tab);
	if (s->env)
		free_env(s->env);
	if (s->dup_env)
		free_env(s->dup_env);
	if (s->infile)
		free(s->infile);
	if (s->outfile)
		free(s->outfile);
	free(s->str);
	if (s->file->files)
		flush_files(s->file, s);
	ft_free_changed_list(s->head_ll);
	if (s->count_pipes)
	{
		close(s->pipe[0]);
		close(s->pipe[1]);
	}
	rl_clear_history();
	exit(ex);
}
