/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarts <tmarts@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 15:29:48 by tmarts            #+#    #+#             */
/*   Updated: 2023/07/26 20:12:40 by tmarts           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static int	atoi_negative(char *c)
{
	if (*c == '-')
		return (-1);
	else
		return (1);
}

static int	is_int_min(long long int neg_pos, \
		long long int intvalue, char c, long long int *data)
{
	if (neg_pos == -1 && intvalue * -10 - (c - '0') == LLONG_MIN)
	{
		*data = INT_MIN;
		return (1);
	}
	return (0);
}

int	ft_atoi_secure(const char *str, long long int *data)
{
	long long int		intvalue;
	long long int		neg_pos;
	char				*chr;

	intvalue = 0;
	neg_pos = 1;
	chr = (char *)str;
	while (chr && (*chr == ' ' || *chr == '\t'))
		chr++;
	if (chr && (*chr == '-' || *chr == '+') && *(chr + 1) != '\0')
		neg_pos = atoi_negative(chr++);
	while (chr && *chr != '\0')
	{
		if (!(*chr >= '0' && *chr <= '9'))
			return (EXIT_FAILURE);
		if (is_int_min(neg_pos, intvalue, *chr, data))
			return (EXIT_SUCCESS);
		if (intvalue > (LLONG_MAX - (*chr - '0')) / 10)
			return (EXIT_FAILURE);
		intvalue = intvalue * 10 + (*chr - '0');
		chr++;
	}
	*data = (int)(intvalue * neg_pos);
	return (EXIT_SUCCESS);
}
