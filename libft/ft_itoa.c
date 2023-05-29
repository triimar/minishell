/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarts <tmarts@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 19:51:36 by tmarts            #+#    #+#             */
/*   Updated: 2023/03/03 15:28:35 by tmarts           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
Allocates (with malloc(3)) and returns a string
representing the integer received as an argument.
*/

static int	ft_intlen(int n)
{
	int				length;
	long long int	div;

	length = 0;
	div = n;
	if (n <= 0)
		length++;
	while (div != 0)
	{
		length++;
		div = div / 10;
	}
	return (length);
}		

static int	ft_is_neg(int n)
{
	if (n < 0)
		return (1);
	return (0);
}

char	*ft_itoa(int n)
{	
	char			*n_char;
	int				length;
	long long int	div;

	div = n;
	length = ft_intlen(n);
	n_char = malloc (length + 1);
	if (!n_char)
		return (NULL);
	n_char[length] = 0;
	length = length - 1;
	if (ft_is_neg(n))
	{
		n_char[0] = '-';
		div = -div;
	}
	while (length >= ft_is_neg(n))
	{
		n_char[length] = div % 10 + '0';
		length--;
		div = div / 10;
	}
	return (n_char);
}		
