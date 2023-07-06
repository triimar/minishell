/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunskim <eunskim@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 18:18:08 by eunskim           #+#    #+#             */
/*   Updated: 2023/07/06 20:26:41 by eunskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

// char	*tmp1;
// char	*tmp2;

// cnt = 1;
// quote = *(str + *idx);
// tmp1 = ft_strdup_pt((const char *) str, str + *idx);
// while (*(str + *idx + cnt) != quote)
// 	cnt++;
// tmp2 = ft_strdup_pt((const char *) str + *idx + 1, str + *idx + cnt);

// copy everything before the quote
// copy everything between the quotes
// copy everything after the quote

// expand string inside the quotes one by one
// copy everything brfore $
// copy everything after the key(name)

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
		return (NULL);
	}
	memmove(result, str, *i);
	memmove(result + *i, str + *i + 1, cnt);
	memmove(result + *i + cnt, str + *i + cnt + 2, strlen - *i - cnt - 2);
	*i = *i + cnt - 1;
	free(str);
	return (result);
}

char	*double_quote_expansion(char *str, int *idx, t_var_list *var_head, bool *malloc_failed)
{
	int		cnt;
	char	*result;

	cnt = 0;
	while (cnt < *idx)
	{
		cnt++;
	}
	return (result);
}

char	*quote_removal_here_end(char *here_end, t_var_list *var_head, bool *malloc_failed)
{
	int		i;

	i = 0;
	while (*(here_end + i) != '\0')
	{
		if (malloc_failed == true)
			break ;
		if (*(here_end + i) == '\"' || *(here_end + i) == '\'')
			here_end = quote_removal(here_end, &i, malloc_failed);
		i++;
	}
	return (here_end);
}

char	*expander(char *to_expand, t_var_list *var_head, bool *malloc_failed)
{
	int	i;

	i = 0;
	while (*(to_expand + i) != '\0')
	{
		if (malloc_failed == true)
			break ;
		if (*(to_expand + i) == '\"')
			to_expand = double_quote_expansion(to_expand, &i, var_head, malloc_failed);
		if (*(to_expand + i) == '\'')
			to_expand = quote_removal(to_expand, &i, malloc_failed);
		i++;
	}
	return (to_expand);
}
