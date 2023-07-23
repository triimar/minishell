/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarts <tmarts@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 16:05:21 by tmarts            #+#    #+#             */
/*   Updated: 2023/07/23 22:41:59 by tmarts           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"


int	builtin_unset(t_var_list *var_head, char *cmd)
{
	int			arg_count;
	int			index;
	t_var_list	*node_found;

	index = 1;
	arg_count = get_arg_count(cmd);
	if (arg_count == 1)
		return (0);
	while (cmd && *(cmd + index))
	{
		if (is_valid_identifier(*(cmd + index)))
		{
			node_found = get_node(var_head, *(cmd + index));
			if (node_found != NULL)
			{
				if (modify_var_list_node(node_found, *(cmd + index)) != 0)
					return (1);
				node_found->env_flag = 1;
			}					
			else if (add_to_var_list(var_head, *(cmd + index), 1) != 0)
				return (1);
		}
		index++;
	}
	return (g_exit_code);
}