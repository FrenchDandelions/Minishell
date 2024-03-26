/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thole <thole@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 17:05:09 by thole             #+#    #+#             */
/*   Updated: 2024/03/09 17:05:13 by thole            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static char	*find_path(char **env, char *s)
{
	int	i;
	int	j;

	i = 0;
	while (ft_strcmp2(env[i], s) != 0 && env[i])
		i++;
	j = 0;
	if (env[i] == NULL)
		return (ft_strdup("0"));
	while (env[i][j] && env[i][j] != '=')
		j++;
	return (ft_strdup(env[i] + j + 1));
}

static char	*check_access(char *path, char *cmd, int *flag)
{
	char	*s1;
	char	*s2;

	s1 = ft_strjoin(path, "/");
	if (!s1)
		return (*flag = 1, NULL);
	s2 = ft_strjoin(s1, cmd);
	if (!s2)
		return (free(s1), *flag = 1, NULL);
	free(s1);
	if (access(s2, F_OK | X_OK) == 0)
		return (s2);
	else
		return (free(s2), NULL);
}

static void	check_all_path(char **all, int *flag)
{
	if (all == NULL)
		*flag = 1;
	return ;
}

static char	*last_check(char **all_path, char *cmd, int *flag, char *path)
{
	if (ft_strcmp2(path, "0") == 1)
		free(path);
	if (all_path)
		free_array(all_path);
	if (!all_path || *flag == 1)
		return (NULL);
	return (ft_strdup(cmd));
}

char	*get_path(char *cmd, char **env, int *flag)
{
	char	*path;
	char	**all_path;
	int		i;
	char	*str;

	if (ft_strchr(cmd, '/'))
		return (ft_strdup(cmd));
	path = find_path(env, "PATH=");
	if (!path)
		return (NULL);
	all_path = ft_split(path, ':');
	check_all_path(all_path, flag);
	i = 0;
	while (all_path[i] != NULL && *flag == 0)
	{
		str = check_access(all_path[i], cmd, flag);
		if (str != NULL)
			return (return_cmd(path, all_path, str));
		i++;
	}
	if (all_path && !all_path[i])
		return (not_found(cmd, all_path, path, &(*flag)));
	return (last_check(all_path, cmd, flag, path));
}
