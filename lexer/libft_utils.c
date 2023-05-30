/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunskim <eunskim@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 20:04:28 by eunskim           #+#    #+#             */
/*   Updated: 2023/05/30 14:57:15 by eunskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;

	i = 0;
	if (dstsize != 0)
	{
		while (i < dstsize - 1 && src[i] != 0)
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = 0;
	}
	while (src[i] != 0)
		i++;
	return (i);
}

char	*ft_strdup(const char *s1)
{
	char	*s1_cpy;
	size_t	size;

	size = ft_strlen(s1) + 1;
	s1_cpy = (char *)malloc(size);
	if (s1_cpy == 0)
		return (0);
	ft_strlcpy(s1_cpy, s1, size);
	return (s1_cpy);
}

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
