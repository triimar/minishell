/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils_1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarts <tmarts@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 16:58:33 by tmarts            #+#    #+#             */
/*   Updated: 2023/01/09 17:46:53 by tmarts           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"

int	ft_putchar_int(int c)
{
	if (write(1, &c, 1) < 0)
		return (-1);
	return (1);
}

int	ft_u_intlen(unsigned int u)
{
	int				length;
	long long int	div;

	length = 0;
	div = u;
	if (div == 0)
		length++;
	while (div != 0)
	{
		length++;
		div = div / 10;
	}
	return (length);
}	

int	ft_hex_len(size_t dec)
{
	int		length;
	size_t	div;

	length = 0;
	div = dec;
	if (div == 0)
		length++;
	while (div != 0)
	{
		length++;
		div = div / 16;
	}
	return (length);
}	

char	*ft_itoa_u(unsigned int u)
{	
	char			*n_char;
	int				length;
	long long int	div;

	div = u;
	length = ft_u_intlen(u);
	n_char = malloc (length + 1);
	if (!n_char)
		return (NULL);
	n_char[length] = 0;
	length -= 1;
	while (length >= 0)
	{
		n_char[length] = div % 10 + '0';
		length--;
		div = div / 10;
	}
	return (n_char);
}		

char	*ft_itoa_hex(size_t dec, char x_case)
{
	char				*x_char;
	int					length;
	size_t				div;
	int					reminder;

	div = dec;
	length = ft_hex_len(dec);
	x_char = malloc (length + 1);
	if (!x_char)
		return (NULL);
	x_char[length] = 0;
	length -= 1;
	while (length >= 0)
	{
		reminder = div % 16;
		if (reminder < 10)
			x_char[length] = reminder + '0';
		else if (reminder >= 10)
				x_char[length] = (reminder - 10) + (x_case - 23);
		length--;
		div = div / 16;
	}
	return (x_char);
}
