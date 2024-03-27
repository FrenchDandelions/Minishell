/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprintf.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thole <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 14:46:54 by thole             #+#    #+#             */
/*   Updated: 2024/03/27 15:10:48 by andrew           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPRINTF_H
# define SPRINTF_H

# include "../libft.h"
# include <stdlib.h>

typedef struct s_sprintf
{
	size_t	length;
	size_t	pos;
	size_t	i;
	char	*string;
}			t_sprintf;

int	ft_sprintf_strdup(const char *s, char **str);
int	ft_sprintf_strdup2(char **str);
int	ft_sprintf_itoa(int n, char **s);
int	ft_sprintf_uitoa(unsigned int n, char **s);
int	ft_sprintf_hexa(unsigned int nb, char *base, char **str);
int	ft_sprintf_pointer(unsigned long long p, char *base, char **str);
int	ft_sprintf(char *buffer, const char *str, ...);
int	ft_getpercent(int c, char **str);

#endif
