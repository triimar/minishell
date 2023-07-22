/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarts <tmarts@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 17:13:10 by eunskim           #+#    #+#             */
/*   Updated: 2023/07/22 22:55:10 by tmarts           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static void	export_no_args(t_var_list *var_head)
{
	t_var_list	*current;

	current = var_head;
	while (current != NULL)
	{
		if (current->env_flag == 1)
		{
			ft_putstr_fd("declare -x ", STDOUT_FILENO);
			ft_putstr_fd(current->key, STDOUT_FILENO);
			if (current->value != NULL)
			{
				ft_putstr_fd("=\"", STDOUT_FILENO);
				ft_putstr_fd(current->value, STDOUT_FILENO);
				ft_putchar_fd('\"', STDOUT_FILENO);
			}
			ft_putchar_fd('\n', STDERR_FILENO);
		}
		current = current->next;
	}
	return ;
}

t_var_list	*find_in_var_list(t_var_list *var_head, char *str)
{
	t_var_list	*current;
	t_var_list	*node_found;

	current = var_head;
	while (current != NULL)
	{
		if ()
		current = current->next;
	}
	return (node_found);
}

int	builtin_export(t_var_list *var_head, char **cmd)
{	
	int	arg_count;
	int	index;

	index = 1;
	arg_count = get_arg_count(cmd);
	if (arg_count == 1)
		export_no_args(var_head);
	while (cmd && *(cmd + index))
	{
		index++;
	}
	return (0);
}
