/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assignments.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarts <tmarts@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 17:37:42 by tmarts            #+#    #+#             */
/*   Updated: 2023/07/22 21:10:23 by tmarts           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

static int	full_assign(t_var_list *new, char *word, char *delim_pt)
{
	new->key = ft_strdup_pt(word, delim_pt);
	if (!new->key)
		return (free(new), 1);
	new->value = ft_strdup(delim_pt + 1);
	if (!new->value)
		return (free(new->key), free(new), 1);
	return (0);
}

t_exec_exit_code	add_to_var_list(t_var_list *var_list, \
													char *str, int flag)
{
	t_var_list		*new_node;
	char			*delim_pt;

	new_node = (t_var_list *)ft_calloc(1, sizeof(t_var_list));
	if (!new_node)
		return (EXEC_MALLOC_ERROR);
	new_node->env_flag = flag;
	delim_pt = ft_strchr(str, '=');
	if (delim_pt == NULL)
	{
		new_node->key = ft_strdup(str);
		if (!new_node->key)
			return (free(new_node), EXEC_MALLOC_ERROR);
	}
	else if (full_assign(new_node, str, delim_pt) != 0)
		return (EXEC_MALLOC_ERROR);
	ft_lstadd_back_ms(&var_list, new_node);
	return (EXEC_SUCCESS);
}

// char	*get_new_key(char *str, char *delimiter)
// {
// 	char			*new_key;

// 	if (delimiter == NULL)
// 		new_key = ft_strdup(str);
// 	else
// 		new_key = ft_strdup_pt(str, delimiter);
// 	if (!new_key)
// 		return (NULL);
// 	return (new_key);
// }

// t_exec_exit_code	add_to_var_list(t_var_list *var_list, \
// 													char *str, int flag)
// {
// 	t_var_list		*new_node;
// 	char			*delim_pt;
// 	char			*new_key;

// 	delim_pt = ft_strchr(str, '=');
// 	new_key = get_new_key(str, delim_pt);
// 	if (!new_key)
// 		exit(MALLOC_ERROR);
// 	if (check_if_in_var_list(var_list, new_key) == true)
// 	{
		
// 	}
// 	else
// 	{
// 		new_node = (t_var_list *)ft_calloc(1, sizeof(t_var_list));
// 		if (!new_node)
// 			return (EXEC_MALLOC_ERROR);
// 		new_node->env_flag = flag;
// 		new_node->key = new_key;
// 		if (delim_pt != NULL)
// 		{
// 			new_node->value = ft_strdup(delim_pt + 1);
// 			if (!new_node->value)
// 				return (free(new_node->key), free(new_node), 1);
// 		}	
// 		ft_lstadd_back_ms(&var_list, new_node);
// 	}
// 	return (EXEC_SUCCESS);
// }

t_exec_exit_code	add_assignments(t_var_list *var_list, \
									t_assignment *assign, int flag)
{
	t_assignment	*cur_assign;

	cur_assign = assign;
	while (cur_assign != NULL)
	{
		if (add_to_var_list(var_list, cur_assign->word, flag))
			return (EXEC_FAIL);
		cur_assign = cur_assign->next;
	}
	return (EXEC_SUCCESS);
}
