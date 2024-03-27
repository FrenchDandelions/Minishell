/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aattali <aattali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 17:31:27 by aattali           #+#    #+#             */
/*   Updated: 2024/03/27 15:04:23 by aattali          ###   ########.fr       */
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
