/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarts <tmarts@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 17:13:10 by eunskim           #+#    #+#             */
/*   Updated: 2023/07/22 21:25:55 by tmarts           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

void	check_if_only_assignments(char **arg)
{
}

int	builtin_export(t_var_list *var_head, char **cmd)
{	
	
}


void	export_no_args(t_var_list *var_head)
{
	t_var_list	*current;

	current = var_head;
	while (current != NULL)
	{
		if (current->env_flag == 1)
		{
			
		}
		current = current->next;
	}
}