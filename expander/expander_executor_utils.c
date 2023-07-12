/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_executor_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunskim <eunskim@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 20:27:31 by eunskim           #+#    #+#             */
/*   Updated: 2023/07/12 21:09:42 by eunskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

void	execute_expander_on_cmd_array(char **cmd, t_var_list *var_head, bool *malloc_failed)
{
	int	i;

	i = 0;
	if (cmd == NULL || *cmd == NULL)
		return ;
	while (cmd + i != NULL)
	{
		*(cmd + i) = expander(*(cmd + i), var_head, malloc_failed);
		i++;
	}
}

// char	*get_assignment_value(char *assignment)
// {
// 	int 	i;
// 	char	*result;

// 	i = 0;
// 	while (*(assignment + i) != '=')
// 		i++;
// 	result = 
	
// }

void	execute_expander_on_assignments(t_assignment *assignments, t_var_list *var_head, bool *malloc_failed)
{
	t_assignment	*tmp;
	// char			*to_expand;

	tmp = assignments;
	while (assignments)
	{
		if (*malloc_failed == true)
			break ;
		// to_expand =
		tmp->word = expander(tmp->word, var_head, malloc_failed);
		tmp = tmp->next;
	}
}

void	execute_expander_on_redirect_list(t_redirect *redirect, t_var_list *var_head, bool *malloc_failed)
{
	t_redirect	*tmp;

	tmp = redirect;
	while (tmp)
	{
		if (*malloc_failed == true)
			break ;
		if (tmp->type == REDIRECT_HERE_DOC)
			tmp->word = quote_removal_here_end(tmp->word, malloc_failed);
		else
			tmp->word = expander(tmp->word, var_head, malloc_failed);
		tmp = tmp->next;
	}
}

void	execute_expander_on_content(t_ast_content *content, t_var_list *var_head, bool *malloc_failed)
{
	execute_expander_on_redirect_list(content->stdin_redirect, var_head, malloc_failed);
	execute_expander_on_redirect_list(content->stdout_redirect, var_head, malloc_failed);
	execute_expander_on_assignments(content->assignments, var_head, malloc_failed);
	execute_expander_on_cmd_array(content->cmd, var_head, malloc_failed);
}

void	execute_expander_on_tree(t_ast *node, t_var_list *var_head, bool *malloc_failed)
{
	if (node == NULL)
		return ;
	if (*malloc_failed == true)
		return ;
	execute_expander_on_tree(node->left, var_head, malloc_failed);
	execute_expander_on_tree(node->right, var_head, malloc_failed);
	if (node->content)
		execute_expander_on_content(node->content, var_head, malloc_failed);
}
