/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarts <tmarts@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 17:16:20 by tmarts            #+#    #+#             */
/*   Updated: 2023/03/03 15:49:50 by tmarts           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
Locates the last occurrence of c (converted to a char) in the string 
pointed to by s. The terminating null character is considered to be 
part of the string; therefore if c is `\0', the functions locate the 
terminating `\0'.
Returns a pointer to the located character, or NULL if the character 
does not appear in the string.
*/

char	*ft_strrchr(const char *s, int c)
{
	unsigned int	slen;

	slen = ft_strlen(s);
	while ((slen > 0) && *(s + slen) != (const char)c)
		slen--;
	if (*(s + slen) == (const char)c)
		return ((char *)(s + slen));
	return (0);
}
