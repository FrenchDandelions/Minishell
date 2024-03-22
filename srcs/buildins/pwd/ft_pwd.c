/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thole <thole@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 17:31:27 by thole             #+#    #+#             */
/*   Updated: 2024/03/20 17:31:29 by thole            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

void	ft_pwd(t_struct *s)
{
	char	str[PATH_MAX];

	if (getcwd(str, PATH_MAX))
		printf("%s\n", str);
	else
	{
		perror("getcwd");
		free_all(s, 1);
	}
	free_all(s, 0);
}
