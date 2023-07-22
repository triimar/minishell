/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_envp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarts <tmarts@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 20:05:06 by tmarts            #+#    #+#             */
/*   Updated: 2023/07/22 17:51:40 by tmarts           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

static int	ft_envp_lstsize(t_var_list *lst)
{
	int			length;
	t_var_list	*current;

	current = lst;
	length = 0;
	while (current != NULL)
	{
		if (current->env_flag == 0 || current->key == NULL)
			current = current->next;
		else
		{
			current = current->next;
			length++;
		}
	}
	return (length);
}

t_exec_exit_code	get_envp(t_exec *s_exec, t_var_list *var_list)
{
	t_var_list	*cur_node;
	int			len;
	int			i;

	i = 0;
	cur_node = var_list;
	len = ft_envp_lstsize(var_list);
	s_exec->envp = ft_calloc(len + 1, sizeof (char *));
	if (!s_exec->envp)
		return (EXEC_MALLOC_ERROR);
	while (i < len)
	{
		if (cur_node->env_flag == 0 || cur_node->key == NULL)
			cur_node = cur_node->next;
		else
		{
			s_exec->envp[i] = \
				ft_strjoin_sym(cur_node->key, cur_node->value, '=');
			if (!s_exec->envp[i])
				return (ft_free_pp_n(s_exec->envp, i), EXEC_MALLOC_ERROR);
			cur_node = cur_node->next;
			i++;
		}
	}
	return (EXEC_SUCCESS);
}
