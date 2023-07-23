/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assignments.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarts <tmarts@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 17:37:42 by tmarts            #+#    #+#             */
/*   Updated: 2023/07/23 21:30:08 by tmarts           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

t_exec_exit_code	add_assignments(t_var_list *var_list, t_assignment *assign)
{
	t_assignment	*cur_assign;
	t_var_list		*node_found;

	cur_assign = assign;
	while (cur_assign != NULL)
	{
		node_found = get_var_list_node(var_list, cur_assign->word);
		if (node_found == NULL && \
			add_to_var_list(var_list, cur_assign->word, 0) != 0)
			return (EXEC_MALLOC_ERROR);
		else if (node_found != NULL && \
			modify_var_list_node(node_found, cur_assign->word) != 0)
			return (EXEC_MALLOC_ERROR);
		cur_assign = cur_assign->next;
	}
	return (EXEC_SUCCESS);
}
