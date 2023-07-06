/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_executor.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunskim <eunskim@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 20:27:31 by eunskim           #+#    #+#             */
/*   Updated: 2023/07/06 14:40:01 by eunskim          ###   ########.fr       */
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
		expander(*(cmd + i), var_head, malloc_failed);
		i++;
	}
}

void	execute_expander_on_assignments(t_assignment *assignments, t_var_list *var_head, bool *malloc_failed)
{
	t_assignment	*tmp;

	tmp = assignments;
	while (assignments)
	{
		if (malloc_failed == true)
			break ;
		expander(tmp->word, var_head, malloc_failed);
		tmp = tmp->next;
	}
}

void	execute_expander_on_redirect_list(t_redirect *redirect, t_var_list *var_head, bool *malloc_failed)
{
	t_redirect	*tmp;

	tmp = redirect;
	while (tmp)
	{
		if (malloc_failed == true)
			break ;
		if (tmp->type == REDIRECT_HERE_DOC)
			quote_removal_here_end(tmp->word, var_head, malloc_failed);
		else
			expander(tmp->word, var_head, malloc_failed);
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
	if (malloc_failed == true)
		return ;
	execute_expander_on_tree(node->left, var_head, malloc_failed);
	execute_expander_on_tree(node->right, var_head, malloc_failed);
	if (node->content)
		execute_expander_on_content(node->content, var_head, malloc_failed);
}

t_expander_exit_code	expander_executor(t_ast *ast_root, t_var_list *var_head)
{
	bool	malloc_failed;

	malloc_failed = false;
	execute_expander_on_tree(ast_root, var_head, &malloc_failed);
	if (malloc_failed == true)
		return (EXPANDER_FAILURE);
	return (EXPANDER_SUCCESS);
}
