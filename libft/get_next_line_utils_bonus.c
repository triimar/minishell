/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarts <tmarts@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 22:04:27 by tmarts            #+#    #+#             */
/*   Updated: 2023/02/27 14:43:58 by tmarts           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"
#include "libft.h"

/* 
ft size_t	ft_linelen(const char *str)
Returns the number of characters in a string until '\n', including '\n' 
*/
size_t	ft_linelen(const char *str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] == '\n')
		{
			i++;
			return (i);
		}
		i++;
	}
	return (0);
}

/*
char	*ft_strljoin(char *s1, char *s2, int len_s2)
Allocates and returns a new string, which is the result of the 
concatenation of ’s1’ and maximum of len_s2 characters of ’s2’. 
Function frees 's1' after the concatenation
*/
char	*ft_strljoin(char *s1, char *s2, int len_s2)
{
	char	*string;
	int		s1_len;
	int		j;

	if (len_s2 == 0)
		return (s1);
	if (s1 == 0)
	{
		string = ft_strndup(s2, len_s2);
		return (string);
	}	
	s1_len = ft_strlen(s1);
	string = malloc(s1_len + len_s2 + 1 * sizeof(char));
	if (!string)
		return (free (s1), NULL);
	while (*s1 != 0)
		*string++ = *s1++;
	j = 0;
	while (j++ != len_s2)
		*string++ = *s2++;
	*string = 0;
	free(s1 - s1_len);
	return (string - s1_len - len_s2);
}

/* 
char	*ft_strndup(const char *str, size_t len)
Returns a pointer to a null-terminated byte string, which contains 
copies of at most size bytes from the string pointed to by str
*/
char	*ft_strndup(const char *str, size_t len)
{
	char	*dst;

	if (!str || len == 0)
		return (NULL);
	dst = malloc((len + 1) * sizeof(char));
	if (!dst)
		return (NULL);
	ft_strlcpy(dst, str, len + 1);
	return (dst);
}
