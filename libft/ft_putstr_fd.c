/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarts <tmarts@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 15:42:34 by tmarts            #+#    #+#             */
/*   Updated: 2023/03/03 14:32:50 by tmarts           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
Outputs the string ’s’ to the given file
descriptor.
*/

void	ft_putstr_fd(char *s, int fd)
{
	write(fd, s, ft_strlen(s));
}
