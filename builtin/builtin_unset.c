/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarts <tmarts@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 16:05:21 by tmarts            #+#    #+#             */
/*   Updated: 2023/07/27 17:15:40 by tmarts           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

// static int	unset_is_valid_identifier(char *cmd)
// {
	// if (*cmd == '_' && ft_strchr(cmd, '=') == NULL)
	// 	return (1);
	// if (!ft_isalpha(*cmd) || ft_strchr(cmd, '=') != NULL)
	// {
	// 	error_printer("unset", cmd, "not a valid identifier");
	// 	g_exit_code = 1;
	// 	return (0);
	// }

static int	unset_is_valid_identifier(char *cmd)
{
	int	i;

	i = 1;
	if (!ft_isalpha(cmd[0]) && cmd[0] != '_')
	{
		error_printer("unset", cmd, "not a valid identifier");
		return (0);
	}
	while (cmd[i] != '\0')
	{
		if (!ft_isalnum(cmd[i]) && cmd[i] != '_')
		{
			error_printer("unset", cmd, "not a valid identifier");
			return (0);
		}
		i++;
	}
	return (1);
}

static t_var_list	*get_previous(t_var_list *var_head, t_var_list *found_node)
{
	t_var_list	*current;
	t_var_list	*previous;

	previous = NULL;
	current = var_head;
	while (current != found_node)
	{
		previous = current;
		current = current->next;
	}
	return (previous);
}

static void	free_single_var_node(t_var_list *node)
{
	if (node->key)
		free(node->key);
	if (node->value)
		free(node->value);
	free(node);
}

static void	remove_found_node(t_minishell *ms_data, t_var_list *found_node)
{
	t_var_list	*previous_node;

	previous_node = get_previous(ms_data->var_head, found_node);
	if (previous_node == NULL)
		ms_data->var_head = ms_data->var_head->next;
	else
		previous_node->next = found_node->next;
	free_single_var_node(found_node);
}

int	builtin_unset(t_minishell *ms_data, char **cmd)
{
	int			arg_count;
	int			index;
	int			return_value;
	t_var_list	*node_found;

	index = 1;
	return_value = 0;
	arg_count = get_arg_count(cmd);
	if (arg_count == 1)
		return (return_value);
	while (cmd && *(cmd + index))
	{
		if (unset_is_valid_identifier(*(cmd + index)))
		{
			node_found = get_var_list_node(ms_data->var_head, *(cmd + index));
			if (node_found != NULL)
				remove_found_node(ms_data, node_found);
		}
		else
			return_value = 1;
		index++;
	}
	return (return_value);
}
