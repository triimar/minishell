/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarts <tmarts@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 14:04:45 by tmarts            #+#    #+#             */
/*   Updated: 2023/03/03 15:57:33 by tmarts           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	dstlen;
	size_t	srclen;
	size_t	i;

	srclen = ft_strlen(src);
	if (!dst && dstsize == 0)
		return (srclen);
	dstlen = ft_strlen(dst);
	i = 0;
	if (dstsize != 0 && dstlen < dstsize)
	{
		while (*(src + i) != 0 && i < (dstsize - dstlen - 1))
		{
			*(dst + dstlen + i) = *(src + i);
			i++;
		}
		*(dst + dstlen + i) = 0;
		return (dstlen + srclen);
	}
	return (srclen + dstsize);
}
