/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunskim <eunskim@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 19:47:18 by eunskim           #+#    #+#             */
/*   Updated: 2023/07/04 21:19:05 by eunskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

static int	ft_strcmp(const char *s1, const char *s2)
{
	if (s1 == 0 || s2 == 0)
		return (0);
	while (*s1 != '\0' && *s2 != '\0' && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	if (*s1 || *s2)
		return (0);
	return (1);
}

char	*get_value_for_key(t_var_list *var_head, const char *key)
{
	t_var_list	*tmp;
	char		*value;

	tmp = var_head;
	value = NULL;
	while (tmp)
	{
		if (ft_strcmp((const char *) var_head->key, key))
		{
			value = var_head->value;
			break ;
		}
		tmp = tmp->next;
	}
	return (value);
}


t_expander_exit_code	execute_on_content(t_ast_node *node)
{
	
	execute_on_redirect_list();
	execute_on_redirect_list();
	execute_on_assignments();
	execute_on_string_array();
}

void	execute_on_tree(t_ast_node *node, bool *malloc_failed)
{
	if (node == NULL)
		return ;
	if (malloc_failed == true)
		return ;
	execute_on_tree(node->left);
	execute_on_tree(node->right);
	if (node->content)
		*malloc_failed = (bool) execute_on_content();
}