/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_executor_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunskim <eunskim@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 20:27:31 by eunskim           #+#    #+#             */
/*   Updated: 2023/07/13 17:54:42 by eunskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

void	execute_expander_on_cmd_array(char **cmd, \
t_var_list *var_head, bool *malloc_failed)
{
	int	i;

	i = 0;
	if (cmd == NULL || *cmd == NULL)
		return ;
	while (*(cmd + i) != NULL)
	{
		*(cmd + i) = expander(*(cmd + i), var_head, malloc_failed);
		i++;
	}
}

void	execute_expander_on_assignments(t_assignment *assignments, \
t_var_list *var_head, bool *malloc_failed)
{
	t_assignment	*tmp;
	char			*prefix;
	char			*to_expand;
	int				i;

	tmp = assignments;
	while (tmp)
	{
		i = 0;
		if (*malloc_failed == true)
			break ;
		while (*(tmp->word + i) != '=')
			i++;
		prefix = ft_strdup_pt(tmp->word, tmp->word + i + 1);
		if (prefix == NULL)
		{
			*malloc_failed = true;
			return ;
		}
		to_expand = ft_strdup(tmp->word + i + 1);
		if (to_expand == NULL)
		{
			*malloc_failed = true;
			free(prefix);
			return ;
		}
		to_expand = expander(to_expand, var_head, malloc_failed);
		free(tmp->word);
		tmp->word = ft_strjoin(prefix, to_expand);
		tmp = tmp->next;
	}
}

void	execute_expander_on_redirect_list(t_redirect *redirect, \
t_var_list *var_head, bool *malloc_failed)
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

void	execute_expander_on_content(t_ast_content *content, \
t_var_list *var_head, bool *malloc_failed)
{
	execute_expander_on_redirect_list(content->stdin_redirect, \
	var_head, malloc_failed);
	execute_expander_on_redirect_list(content->stdout_redirect, \
	var_head, malloc_failed);
	execute_expander_on_assignments(content->assignments, \
	var_head, malloc_failed);
	execute_expander_on_cmd_array(content->cmd, \
	var_head, malloc_failed);
}

void	execute_expander_on_tree(t_ast *node, \
t_var_list *var_head, bool *malloc_failed)
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
