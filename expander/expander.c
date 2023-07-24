/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunskim <eunskim@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 18:18:08 by eunskim           #+#    #+#             */
/*   Updated: 2023/07/24 18:28:25 by eunskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

char	*variable_expansion(char *str, int *i, \
t_var_list *var_head, bool *malloc_failed)
{
	int		cnt;
	int		strlen_value;
	char	*tmp;
	char	*value;

	cnt = check_key_len(str, *i);
	if (cnt == 1)
		return (str);
	tmp = ft_strdup_pt(str + *i + 1, str + *i + cnt);
	if (tmp == NULL)
		return (*malloc_failed = true, str);
	value = return_value_str(var_head, tmp, malloc_failed);
	if (*malloc_failed == true)
		return (free(tmp), str);
	strlen_value = check_value_len(value);
	free(tmp);
	tmp = ft_calloc(1, ft_strlen(str) + strlen_value - cnt + 1);
	if (tmp == NULL)
		return (*malloc_failed = true, str);
	ft_memmove(tmp, str, *i);
	ft_memmove(tmp + *i, value, strlen_value);
	ft_memmove(tmp + *i + strlen_value, str + *i + cnt, \
	ft_strlen(str) - *i - cnt);
	*i = *i + strlen_value - 1;
	return (free(str), tmp);
}

char	*substring_expansion(char *str, \
t_var_list *var_head, bool *malloc_failed)
{
	int		i;

	i = 0;
	if (str == NULL)
		return (NULL);
	while (*(str + i) != '\0')
	{
		if (*(str + i) == '$')
			str = variable_expansion(str, &i, var_head, malloc_failed);
		if (*malloc_failed == true)
			return (str);
		i++;
	}
	return (str);
}

char	*double_quote_expansion(char *str, int *i, \
t_var_list *var_head, bool *malloc_failed)
{
	int		cnt;
	int		substrlen;
	char	*substr;
	char	*result;

	cnt = 0;
	substrlen = 0;
	while (*(str + *i + cnt + 1) != '\"')
		cnt++;
	substr = ft_strdup_pt(str + *i, str + *i + cnt + 2);
	if (substr == NULL)
		return (*malloc_failed = true, str);
	substr = substring_expansion(substr, var_head, malloc_failed);
	if (*malloc_failed == true)
		return (str);
	substrlen = ft_strlen(substr);
	result = ft_calloc(1, ft_strlen(str) - cnt - 2 + substrlen - 2 + 1);
	if (result == NULL)
		return (*malloc_failed = true, free(substr), str);
	ft_memmove(result, str, *i);
	ft_memmove(result + *i, substr + 1, substrlen - 2);
	ft_memmove(result + *i + substrlen - 2, \
	str + *i + cnt + 2, ft_strlen(str) - *i - cnt - 2);
	*i = *i + substrlen - 2 - 1;
	return (free(substr), free(str), result);
}

char	*expander(char *to_expand, t_var_list *var_head, bool *malloc_failed)
{
	int	i;

	i = 0;
	if (to_expand == NULL)
		return (NULL);
	while (*(to_expand + i) != '\0')
	{
		if (*(to_expand + i) == '\"' \
		|| *(to_expand + i) == '\'' || *(to_expand + i) == '$')
		{
			if (*(to_expand + i) == '\"')
				to_expand = \
				double_quote_expansion(to_expand, &i, var_head, malloc_failed);
			else if (*(to_expand + i) == '\'')
				to_expand = quote_removal(to_expand, &i, malloc_failed);
			else
				to_expand = \
				variable_expansion(to_expand, &i, var_head, malloc_failed);
		}
		if (*malloc_failed == true)
			break ;
		i++;
	}
	return (to_expand);
}

t_expander_exit_code	expander_executor(t_parser *parser_data, \
t_var_list *var_head)
{
	bool	malloc_failed;

	if (parser_data->ast_root == NULL)
		return (EXPANDER_SUCCESS);
	malloc_failed = false;
	execute_expander_on_tree(parser_data->ast_root, var_head, &malloc_failed);
	if (malloc_failed == true)
		return (free_ast(parser_data), EXPANDER_FAILURE);
	return (EXPANDER_SUCCESS);
}
