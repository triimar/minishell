/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarts <tmarts@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 16:24:59 by tmarts            #+#    #+#             */
/*   Updated: 2023/03/03 15:28:15 by tmarts           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
Contiguously allocates enough space for count objects that are size bytes 
of memory each and returns a pointer to the allocated memory.  
The allocated memory is filled with bytes of value zero.
*/

// void	*ft_calloc(size_t count, size_t size)
// {
// 	void	*ptr;

// 	if (size != 0 && count > SIZE_MAX / size)
// 		return (NULL);
// 	ptr = malloc(count * size);
// 	if (!ptr)
// 		return (NULL);
// 	ft_bzero(ptr, count * size);
// 	return (ptr);
// }

void	*ft_calloc(size_t count, size_t size)
{
	unsigned char	*ptr;
	size_t			i;

	if (size != 0 && count > SIZE_MAX / size)
		return (NULL);
	ptr = malloc(count * size);
	if (!ptr)
		return (NULL);
	i = 0;
	while (i < count * size)
	{
		ptr[i] = 0;
		i++;
	}
	return ((void *)ptr);
}
