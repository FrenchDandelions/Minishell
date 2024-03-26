/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_path_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thole <thole@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 17:30:07 by thole             #+#    #+#             */
/*   Updated: 2024/03/22 17:30:09 by thole            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_strcmp2(char *s1, char *s2)
{
	int	i;

	i = 0;
	if (!s1)
		return (1);
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	if (s2[i] == '\0')
		return (0);
	return (1);
}

void	path_not_found(t_struct *s, char *cmd)
{
	ft_putstr_fd("Minishell: ", STDERR_FILENO);
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putstr_fd(": command not found", STDERR_FILENO);
	free_all(s, 127);
}

char	*not_found(char *cmd, char **all_path, char *path, int *flag)
{
	if (path)
		free(path);
	if (all_path)
		free_array(all_path);
	(*flag) = 2;
	ft_putstr_fd("Minishell: ", STDERR_FILENO);
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putstr_fd(": command not found", STDERR_FILENO);
	return (ft_strdup(cmd));
}

char	*return_cmd(char *path, char **all_path, char *str)
{
	if (path)
		free(path);
	if (all_path)
		free_array(all_path);
	return (str);
}
