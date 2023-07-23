/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarts <tmarts@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 17:13:10 by eunskim           #+#    #+#             */
/*   Updated: 2023/07/23 17:34:39 by tmarts           ###   ########.fr       */
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

static int	ft_sub_len(char const *start, char c)
{
	int	len;

	len = 0;
	while (*(start + len) != 0 && *(start + len) != c)
		len++;
	return (len);
}

t_var_list	*get_var_list_node(t_var_list *var_head, char *str)
{
	t_var_list	*current;
	int			newkey_len;

	newkey_len = ft_sub_len(str, '=');
	current = var_head;
	while (current != NULL)
	{
		if (ft_strncmp(current->key, str, newkey_len) == 0 \
			&& (int)ft_strlen(current->key) == newkey_len)
			return (current);
		current = current->next;
	}
	return (NULL);
}

int	builtin_export(t_var_list *var_head, char **cmd)
{	
	int			arg_count;
	int			index;
	char		*delimiter;
	t_var_list	*matching_node;

	index = 1;
	arg_count = get_arg_count(cmd);
	if (arg_count == 1)
		export_no_args(var_head);
	while (cmd && *(cmd + index))
	{
		matching_node = get_var_list_node(var_head, *(cmd + index));
		if (matching_node == NULL)
			return (0);
			// printf("\nNO MATCH\n");
		else
		{	
			// printf("\nKEY=[%s]     VALUE=[%s]     FLAG=[%d]\n", matching_node->key, matching_node->value, matching_node->env_flag);
			delimiter = ft_strchr(*(cmd + index), '=');
			if (delimiter == NULL)
				matching_node->env_flag = 1;
			else
			{
				free(matching_node->value);
				matching_node->value = ft_strdup(delimiter + 1);
			}
			// printf("\nKEY=[%s]     VALUE=[%s]     FLAG=[%d]\n", matching_node->key, matching_node->value, matching_node->env_flag);
		}
		index++;
	}
	return (0);
}
