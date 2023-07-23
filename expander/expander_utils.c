/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunskim <eunskim@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 19:47:18 by eunskim           #+#    #+#             */
/*   Updated: 2023/07/23 15:36:03 by eunskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

int	check_value_len(char *value)
{
	if (value == NULL)
		return (0);
	else
		return (ft_strlen(value));
}

int	check_key_len(char *str, int i)
{
	int	cnt;

	cnt = 1;
	if (*(str + i + cnt) == '?')
		return (2);
	while (ft_isdigit(*(str + i + cnt)) \
	|| ft_isalpha(*(str + i + cnt)) || *(str + i + cnt) == '_')
		cnt++;
	return (cnt);
}

/* char	*ft_strndup_pt(const char *start, char *delimiter)
Returns a pointer to a null-terminated byte string, which contains 
copies of at most size bytes from the string pointed to by str */
char	*ft_strdup_pt(const char *start, char *delimiter)
{
	int		i;
	int		len;
	char	*dst;

	i = 0;
	len = 0;
	if (!start || !delimiter || delimiter < start)
		return (NULL);
	while (start + len != delimiter && *(start + len) != '\0')
		len++;
	dst = ft_calloc(1, (len + 1) * sizeof(char));
	if (!dst)
		return (NULL);
	while (i < len)
	{
		dst[i] = start[i];
		i++;
	}
	return (dst);
}

int	ft_strcmp(const char *s1, const char *s2)
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
	// if (ft_strcmp("?", key))
		//
	while (tmp)
	{
		if (ft_strcmp((const char *) tmp->key, key))
		{
			value = tmp->value;
			break ;
		}
		tmp = tmp->next;
	}
	return (value);
}
