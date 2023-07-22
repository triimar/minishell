/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarts <tmarts@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 16:56:16 by eunskim           #+#    #+#             */
/*   Updated: 2023/07/22 22:15:44 by tmarts           ###   ########.fr       */
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

int	get_arg_count(char **cmd)
{
	int	arg_count;

	arg_count = 0;
	while (cmd && *(cmd + arg_count) != NULL)
		arg_count++;
	return (arg_count);
}