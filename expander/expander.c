/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunskim <eunskim@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 18:18:08 by eunskim           #+#    #+#             */
/*   Updated: 2023/07/12 17:09:38 by eunskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

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
	ft_memmove(result, str, *i);
	ft_memmove(result + *i, value, ft_strlen(value));
	ft_memmove(result + *i + ft_strlen(value), str + *i + cnt, ft_strlen(str) - *i - cnt);
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
			result = variable_expansion(str, &i, var_head, malloc_failed);
		if (malloc_failed == true)
			break ;
		i++;
	}
	return (result);
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
	substr = substring_expansion(substr, var_head, malloc_failed);
	substrlen = ft_strlen(substr);
	result = ft_calloc(1, ft_strlen(str) - cnt - 2 + substrlen);
	if (result == NULL)
	{
		*malloc_failed = true;
		return (str);
	}
	ft_memmove(result, str, *i);
	ft_memmove(result + *i, substr, substrlen);
	ft_memmove(result + *i + substrlen, str + *i + cnt + 2, ft_strlen(str) - *i - cnt - 2);
	*i = *i + substrlen - 1;
	free(substr);
	free(str);
	return (result);
}

char	*expander(char *to_expand, t_var_list *var_head, bool *malloc_failed)
{
	int	i;

	i = 0;
	if (to_expand == NULL)
		return (NULL);
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

t_expander_exit_code	expander_executor(t_ast *ast_root, t_var_list *var_head)
{
	bool	malloc_failed;

	malloc_failed = false;
	execute_expander_on_tree(ast_root, var_head, &malloc_failed);
	if (malloc_failed == true)
		return (EXPANDER_FAILURE);
	return (EXPANDER_SUCCESS);
}
