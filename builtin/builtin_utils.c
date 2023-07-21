/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunskim <eunskim@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 16:56:16 by eunskim           #+#    #+#             */
/*   Updated: 2023/07/21 17:52:34 by eunskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

bool	check_if_in_var_list(t_var_list *var_head, char *key)
{
	t_var_list	*tmp;

	tmp = var_head;
	while (tmp)
	{
		if (ft_strcmp((const char *) tmp->key, key))
			return (true);
		tmp = tmp->next;
	}
	return (false);
}

int	change_value_for_key(t_var_list *var_head, char *key, char *new_value)
{
	t_var_list	*tmp;
	char		*value;

	tmp = var_head;
	value = ft_strdup(new_value);
	if (value == NULL)
		return (EXIT_FAILURE);
	while (tmp)
	{
		if (ft_strcmp((const char *) tmp->key, key))
		{
			free_p(tmp->value);
			tmp->value = value;
			break ;
		}
		tmp = tmp->next;
	}
	return (EXIT_SUCCESS);
}
