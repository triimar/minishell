/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarts <tmarts@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 18:48:45 by tmarts            #+#    #+#             */
/*   Updated: 2023/03/03 14:29:01 by tmarts           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
Applies the function ’f’ to each character of the
string ’s’, and passing its index as first argument
to create a new string (with malloc(3)) resulting
from successive applications of ’f’.
*/

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*new_str;
	int		i;

	if (s == 0 || f == 0)
		return (NULL);
	new_str = (char *)malloc((ft_strlen(s) + 1) * sizeof(char));
	if (!new_str)
		return (NULL);
	i = 0;
	while (*(s + i) != 0)
	{
		*(new_str + i) = f(i, *(s + i));
		i++;
	}
	*(new_str + i) = '\0';
	return (new_str);
}
