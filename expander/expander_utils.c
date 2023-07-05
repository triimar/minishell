/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunskim <eunskim@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 19:47:18 by eunskim           #+#    #+#             */
/*   Updated: 2023/07/05 18:10:21 by eunskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

static int	ft_strcmp(const char *s1, const char *s2)
{
	if (s1 == 0 || s2 == 0)
		return (0);
	while (*s1 != '\0' && *s2 != '\0' && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	if (*s1 || *s2)
		return (0);
	return (1);
}

char	*get_value_for_key(t_var_list *var_head, const char *key)
{
	t_var_list	*tmp;
	char		*value;

	tmp = var_head;
	value = NULL;
	while (tmp)
	{
		if (ft_strcmp((const char *) var_head->key, key))
		{
			value = var_head->value;
			break ;
		}
		tmp = tmp->next;
	}
	return (value);
}

int	double_quote_expansion(char *str)
{
	int	i;

	i = 1;
	while (str[i] != '\"')
	{
		if (str[i] == '$')
		{
			get_variable_name(str + i);
		}
		i++;
	}
}

int remove_quotes(char *str)
{
	int	i;

	i = 0;
	while (true)
	{
		if (str[i] == '\"' || str)
	}
}