/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarts <tmarts@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 01:46:41 by tmarts            #+#    #+#             */
/*   Updated: 2023/03/03 15:26:43 by tmarts           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
writes n zeroed bytes to the string s.  If n is zero, bzero() does nothing.
*/

void	ft_bzero(void *s, size_t n)
{
	ft_memset(s, 0, n);
}
