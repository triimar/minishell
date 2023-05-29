/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarts <tmarts@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 22:52:28 by tmarts            #+#    #+#             */
/*   Updated: 2023/03/03 15:29:35 by tmarts           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
Locates the first occurrence of c (converted to an unsigned char) in string s.
*/

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*string;

	string = (unsigned char *)s;
	while (n > 0)
	{
		if (*string == (unsigned char)c)
			return ((void *)string);
		n--;
		string++;
	}
	return (NULL);
}
