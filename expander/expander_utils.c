/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunskim <eunskim@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 19:47:18 by eunskim           #+#    #+#             */
/*   Updated: 2023/07/26 19:59:43 by eunskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

char	*return_value_str(t_var_list *var_head, char *key, bool *malloc_failed)
{
	char	*tmp;
	char	*value;

	if (ft_strcmp("?", key))
	{
		if (check_if_in_var_list(var_head, "?") == false)
			add_to_var_list(var_head, "?", 0);
		tmp = ft_itoa(g_exit_code);
		if (tmp == NULL)
			return (*malloc_failed = true, NULL);
		if (change_value_for_key(var_head, "?", tmp))
			return (*malloc_failed = true, free(tmp), NULL);
		free(tmp);
	}
	value = get_value_for_key(var_head, key);
	return (value);
}

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
