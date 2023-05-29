/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarts <tmarts@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 17:35:33 by tmarts            #+#    #+#             */
/*   Updated: 2023/03/03 15:32:38 by tmarts           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
Copies n characters from src to dst without considering possible overlap. 
Returns dst.
*/

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char	*to;
	char	*from;

	if (dst == 0 && src == 0)
		return (0);
	to = (char *)dst;
	from = (char *)src;
	while (n != 0)
	{
		*to = *from;
		to++;
		from++;
		n--;
	}
	return (dst);
}
