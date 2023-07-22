/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarts <tmarts@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 18:54:26 by tmarts            #+#    #+#             */
/*   Updated: 2023/07/22 19:18:38 by tmarts           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	builtin_env(t_var_list *var_list)
{
	t_var_list	*current;

	current = var_list;
	while (current != NULL)
	{
		if (current->env_flag == 1)
		{
			if (current->key && current->value)
			{
				ft_putstr_fd(current->key, STDOUT_FILENO);
				ft_putchar_fd('=', STDOUT_FILENO);
				ft_putendl_fd(current->value, STDOUT_FILENO);
			}
		}
		current = current->next;
	}
	return (0);
}
