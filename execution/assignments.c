/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assignments.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarts <tmarts@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 17:37:42 by tmarts            #+#    #+#             */
/*   Updated: 2023/07/21 15:25:32 by tmarts           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

t_exec_exit_code	add_to_var_list(t_var_list *var_list, \
									t_assignment *assign, int flag)
{
	t_assignment	*cur_assign;
	t_var_list		*new_var_node;
	char			*delimiter_pt;

	cur_assign = assign;
	while (cur_assign != NULL)
	{
		new_var_node = (t_var_list *)ft_calloc(1, sizeof(t_var_list));
		if (!new_var_node)
			return (EXEC_MALLOC_ERROR);
		new_var_node->env_flag = flag;
		delimiter_pt = ft_strchr(cur_assign->word, '=');
		new_var_node->key = ft_strdup_pt(cur_assign->word, (delimiter_pt));
		if (!new_var_node->key)
			return (free(new_var_node), EXEC_MALLOC_ERROR);
		if (*(delimiter_pt + 1) != '\0')
		{
			new_var_node->value = ft_strdup(delimiter_pt + 1);
			if (!new_var_node->value)
				return (free(new_var_node->key), free(new_var_node), \
															EXEC_MALLOC_ERROR);
		}	
		ft_lstadd_back_ms(&var_list, new_var_node);
		cur_assign = cur_assign->next;
	}
	return (EXEC_SUCCESS);
}
