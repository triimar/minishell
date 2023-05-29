/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarts <tmarts@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 19:24:21 by tmarts            #+#    #+#             */
/*   Updated: 2022/11/03 14:41:05 by tmarts           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	isfound(const char *haystack, const char *needle)
{
	while (*haystack == *needle && *haystack != 0 && *needle != 0)
	{
		if (*(needle + 1) == 0)
			return (1);
		needle++;
		haystack++;
	}
	return (0);
}

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	len_left;

	len_left = len;
	if (*needle == 0)
		return ((char *)haystack);
	if (len == 0)
		return (NULL);
	if (ft_strlen(haystack) < len)
		len_left = ft_strlen (haystack);
	while (len_left > 0)
	{
		if (ft_strlen(needle) <= len_left && isfound(haystack, needle))
			return ((char *)haystack);
		else
			haystack++;
		len_left--;
	}
	return (NULL);
}
