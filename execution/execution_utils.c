/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarts <tmarts@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 18:07:15 by tmarts            #+#    #+#             */
/*   Updated: 2023/07/11 21:01:24 by tmarts           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	ft_free_pp(char **p_p)
{
	int	i;

	i = 0;
	if (!p_p)
		return ;
	while (p_p[i])
	{
		free(p_p[i]);
		i++;
	}
	free (p_p);
	return ;
}

void	ft_free_pp_n(char **array, int str_count)
{
	str_count--;
	while (str_count >= 0)
	{
		free(array[str_count]);
		str_count--;
	}
	free (array);
	return ;
}

int	get_fork_count(t_parser *parser_data)
{
	int	nr_of_forks;

	nr_of_forks = 1;
	parser_data->ast_current = parser_data->ast_root;
	while (parser_data->ast_current->content == NULL)
	{
		nr_of_forks++;
		parser_data->ast_current = parser_data->ast_current->left;
	}
	return (nr_of_forks);
}

t_ast_content	*get_cmd_node(t_parser *parser_data, int fork_c, int child)
{
	int	counted_nodes;

	counted_nodes = 0;
	parser_data->ast_current = parser_data->ast_root;
	while (parser_data->ast_current->content == NULL)
	{
		if (fork_c - counted_nodes == child)
			return (parser_data->ast_current->right->content);
		counted_nodes++;
		parser_data->ast_current = parser_data->ast_current->left;
	}
	return (parser_data->ast_current->content);
}