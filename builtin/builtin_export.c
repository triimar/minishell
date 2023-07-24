/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarts <tmarts@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 17:13:10 by eunskim           #+#    #+#             */
/*   Updated: 2023/07/24 18:06:22 by tmarts           ###   ########.fr       */
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

static int	is_valid_identifier(char *cmd)
{
	if (!ft_isalpha(*cmd))
	{
		error_printer("export", cmd, "not a valid identifier");
		g_exit_code = 1;
		return (0);
	}
	return (1);
}

int	builtin_export(t_var_list *var_head, char **cmd)
{	
	int			arg_count;
	int			index;
	t_var_list	*node_found;

	index = 1;
	arg_count = get_arg_count(cmd);
	if (arg_count == 1)
		export_no_args(var_head);
	while (cmd && *(cmd + index))
	{
		if (is_valid_identifier(*(cmd + index)))
		{
			node_found = get_var_list_node(var_head, *(cmd + index));
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
