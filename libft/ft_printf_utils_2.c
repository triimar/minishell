/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils_2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarts <tmarts@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 20:21:16 by tmarts            #+#    #+#             */
/*   Updated: 2022/12/08 19:36:18 by tmarts           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"

int	ft_printf_str(char *str)
{
	int	len;

	if (!str)
	{
		if (write(1, "(null)", 6) < 0)
			return (-1);
		else
			return (6);
	}
	len = ft_strlen(str);
	if (write(1, str, len) < 0)
		return (-1);
	return (len);
}

int	ft_printf_num(int num)
{
	int		len;
	char	*str;

	len = 0;
	str = ft_itoa(num);
	if (!str)
		return (-1);
	len = ft_printf_str(str);
	free(str);
	return (len);
}

int	ft_printf_u(unsigned int u_num)
{
	int		len;
	char	*str;

	len = 0;
	str = ft_itoa_u(u_num);
	if (!str)
		return (-1);
	len = ft_printf_str(str);
	free(str);
	return (len);
}

int	ft_printf_hex(size_t x_num, char x_case)
{
	int		len;
	char	*str;

	len = 0;
	str = ft_itoa_hex(x_num, x_case);
	if (!str)
		return (-1);
	len = ft_printf_str(str);
	free(str);
	return (len);
}

int	ft_printf_p(size_t p_dec)
{
	int		len;
	char	*str;

	str = ft_itoa_hex(p_dec, 'x');
	if (!str)
		return (-1);
	len = ft_printf_str("0x");
	if (len < 0)
	{
		free(str);
		return (-1);
	}
	len += ft_printf_str(str);
	free(str);
	return (len);
}
