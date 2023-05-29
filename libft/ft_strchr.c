/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarts <tmarts@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 17:56:44 by tmarts            #+#    #+#             */
/*   Updated: 2023/03/03 15:49:15 by tmarts           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
Locates the first occurrence of c (converted to a char) in the string 
pointed to by s.
The terminating null character is considered to be part of the string; t
herefore if c is `\0', the functions locate the terminating `\0'.
Returns a pointer to the located character, or NULL if the character 
does not appear in the string.
*/

char	*ft_strchr(const char *s, int c)
{
	while (*s != 0 && *s != (const char)c)
		s++;
	if (*s == (const char)c)
		return ((char *)s);
	return (0);
}
