/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunskim <eunskim@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 18:18:08 by eunskim           #+#    #+#             */
/*   Updated: 2023/07/11 20:38:14 by eunskim          ###   ########.fr       */
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
	memmove(result, str, *i);
	memmove(result + *i, str + *i + 1, cnt);
	memmove(result + *i + cnt, str + *i + cnt + 2, strlen - *i - cnt - 2);
	*i = *i + cnt - 1;
	free(str);
	return (result);
}

// expand string inside the quotes one by one in a loop
// copy everything after first " before $
// detect key(name)
// copy expanded value 
// copy everything after the key(name) till final "

// length of result : hi + expanded value + rest of string

// hi"hi$USER'$HOME'hi"hi"hi"

char	*variable_expansion(char *str, int *i, t_var_list *var_head, bool *malloc_failed)
{
	int		cnt;
	int		strlen_result;
	char	*key;
	char	*value;
	char	*result;

	cnt = 1;
	while (ft_isdigit(*(str + *i + cnt)) || ft_isalpha(*(str + *i + cnt)) || *(str + *i + cnt) == '_')
		cnt++;
	key = ft_strdup_pt(str + *i + 1, str + *i + cnt);
	value = get_value_for_key(var_head, key);
	strlen_result = ft_strlen(str) + ft_strlen(value) - cnt;
	result = ft_calloc(1, strlen_result + 1);
	if (result == NULL)
	{
		*malloc_failed = true;
		return (str);
	}
	memmove(result, str, *i);
	memmove(result + *i, value, ft_strlen(value));
	memmove(result + *i + ft_strlen(value), str + *i + cnt, ft_strlen(str) - *i - cnt);
	*i = *i + ft_strlen(value) - 1;
	free(key);
	free(str);
	return (result);	
}

char	*substring_expansion(char *str, t_var_list *var_head, bool *malloc_failed)
{
	int		i;
	char	*result;

	i = 0;
	while (*(str + i) != '\0')
	{
		if (*(str + i) == '$')
		{
			result = variable_expansion(str, &i, var_head, malloc_failed);
		}
			
	}
}

char	*double_quote_expansion(char *str, int *i, t_var_list *var_head, bool *malloc_failed)
{
	int		cnt;
	int		substrlen;
	char	*substr;
	char	*result;

	cnt = 0;
	while (*(str + *i + cnt + 1) != '\"')
		cnt++;
	substr = ft_strdup_pt(str + *i + 1, str + *i + cnt + 1);
	substring_expansion(substr, var_head, malloc_failed);
	substrlen = ft_strlen(substr);
	result = ft_calloc();
	if (result == NULL)
	{
		*malloc_failed = true;
		return (str);
	}
	memmove();
	memmove();
	memmove();
	free(substr);
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

char	*expander(char *to_expand, t_var_list *var_head, bool *malloc_failed)
{
	int	i;

	i = 0;
	while (*(to_expand + i) != '\0')
	{
		if (*(to_expand + i) == '\"' || *(to_expand + i) == '\'')
		{
			if (*(to_expand + i) == '\"')
				to_expand = double_quote_expansion(to_expand, &i, var_head, malloc_failed);
			else
				to_expand = quote_removal(to_expand, &i, malloc_failed);
		}
		if (malloc_failed == true)
			break ;
		i++;
	}
	return (to_expand);
}
 