/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_here_end.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunskim <eunskim@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 17:06:59 by eunskim           #+#    #+#             */
/*   Updated: 2023/07/12 17:08:39 by eunskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

char	*quote_removal(char *str, int *i, bool *malloc_failed)
{
	int		cnt;
	int		strlen;
	char	quote;
	char	*result;

	cnt = 0;
	strlen = (int) ft_strlen(str);
	quote = *(str + *i);
	while (*(str + *i + cnt + 1) != quote)
		cnt++;
	result = ft_calloc(1, strlen - 2 + 1);
	if (result == NULL)
	{
		*malloc_failed = true;
		return (str);
	}
	ft_memmove(result, str, *i);
	ft_memmove(result + *i, str + *i + 1, cnt);
	ft_memmove(result + *i + cnt, str + *i + cnt + 2, strlen - *i - cnt - 2);
	*i = *i + cnt - 1;
	free(str);
	return (result);
}

char	*quote_removal_here_end(char *here_end, t_var_list *var_head, bool *malloc_failed)
{
	int		i;

	i = 0;
	while (*(here_end + i) != '\0')
	{
		if (*(here_end + i) == '\"' || *(here_end + i) == '\'')
			here_end = quote_removal(here_end, &i, malloc_failed);
		if (malloc_failed == true)
			break ;
		i++;
	}
	return (here_end);
}
