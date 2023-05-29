/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunskim <eunskim@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 20:04:28 by eunskim           #+#    #+#             */
/*   Updated: 2023/05/29 16:05:04 by eunskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "lexer.h"
#include "../include/lexer.h"

char	*ft_strchr(const char *s, int c)
{
	if ((char) c == '\0')
		return ((char *)s + ft_strlen(s));
	else
	{
		while (*s)
		{
			if ((char) c == *s)
				return ((char *)s);
			s++;
		}
	}
	return (0);
}

void	ft_putstr_fd(char *s, int fd)
{
	if (!s)
		return ;
	write(fd, s, ft_strlen(s));
}

size_t	ft_strlen(const char *s)
{
	size_t	strlen;

	strlen = 0;
	while (s[strlen] != '\0')
		strlen++;
	return (strlen);
}
