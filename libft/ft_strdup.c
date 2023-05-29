/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarts <tmarts@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 23:16:56 by tmarts            #+#    #+#             */
/*   Updated: 2023/03/03 15:53:16 by tmarts           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
Allocates sufficient memory for a copy of the string s1, does the copy, 
and returns a pointer to it.
*/

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
