/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thole <thole@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 18:13:02 by thole             #+#    #+#             */
/*   Updated: 2024/03/22 18:13:03 by thole            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

size_t	ft_gnl_strlen(char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

size_t	ft_gnl_strlcpy(char *dest, char *src, size_t destsize)
{
	size_t	srcsize;
	size_t	i;

	i = 0;
	srcsize = ft_gnl_strlen(src);
	if (destsize > 0)
	{
		while (i < srcsize && i < destsize - 1)
		{
			dest[i] = src[i];
			i++;
		}
		dest[i] = '\0';
	}
	return (srcsize);
}

char	*ft_gnl_strjoin(char *s1, char *s2, size_t len)
{
	size_t	len1;
	size_t	len2;
	char	*s3;

	len1 = ft_gnl_strlen(s1);
	len2 = len;
	s3 = malloc(sizeof(char) * (len1 + len2 + 1));
	if (!s3)
		return (NULL);
	ft_gnl_strlcpy(s3, s1, len1 + 1);
	ft_gnl_strlcpy((s3 + len1), s2, len2 + 1);
	free(s1);
	return (s3);
}

void	count_pipes(t_struct *s)
{
	t_tokens	*temp;

	temp = s->head_ll;
	while (temp->next)
	{
		if (temp->token == TK_PIPES)
			s->count_pipes++;
		temp = temp->next;
	}
}
