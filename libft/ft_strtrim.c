/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarts <tmarts@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 14:49:38 by tmarts            #+#    #+#             */
/*   Updated: 2023/03/03 14:23:54 by tmarts           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
Allocates (with malloc(3)) and returns a copy of
’s1’ with the characters specified in ’set’ removed
from the beginning and the end of the string.
*/

char	*ft_strtrim(char const *s1, char const *set)
{
	int		len_s1;
	char	*trimmed;
	int		set_start;
	int		set_end;

	len_s1 = ft_strlen(s1);
	set_start = 0;
	set_end = 0;
	while (set_start != len_s1 && ft_strchr(set, s1[set_start]) != 0)
		set_start++;
	while (set_end != len_s1 && ft_strchr(set, s1[len_s1 - 1 - set_end]) != 0)
		set_end++;
	if (len_s1 <= set_start + set_end)
		return (ft_strdup(""));
	trimmed = malloc(len_s1 - set_start - set_end + 1);
	if (!trimmed)
		return (NULL);
	ft_strlcpy(trimmed, &s1[set_start], (len_s1 - set_start - set_end + 1));
	return (trimmed);
}
