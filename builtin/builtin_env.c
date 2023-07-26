/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarts <tmarts@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 18:54:26 by tmarts            #+#    #+#             */
/*   Updated: 2023/07/26 17:00:49 by tmarts           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	builtin_env(t_var_list *var_list, char **cmd)
{
	t_var_list	*current;
	int			arg_count;

	current = var_list;
	arg_count = get_arg_count(cmd);
	if (arg_count > 1)
		return (error_printer(*cmd, *(cmd + 1), \
			"Arguments and options are not supported"), 0);
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
