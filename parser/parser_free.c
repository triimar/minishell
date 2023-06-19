/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_free.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunskim <eunskim@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 12:53:09 by eunskim           #+#    #+#             */
/*   Updated: 2023/06/19 16:01:16 by eunskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	clean_parser_data(t_parser *data)
{
	data->scanner->token_head = NULL;
	data->scanner->token_current = NULL;
	data->scanner = NULL;
}

void	free_ast(t_parser *data)
{
	if (data->ast_root == NULL)
		return ;
	data->ast_current = data->ast_root;
	if (data->ast_current->content == NULL)
	{
		if (data->ast_current->right != NULL)
		{
			free_ast_content(data->ast_current->right->content);
			free(data->ast_current->right);
			data->ast_current->right = NULL;
		}
	}
	else if (data->ast_current->content != NULL)
		free_ast_content(data->ast_current->content);
	data->ast_root = data->ast_current->left;
	data->ast_current->left = NULL;
	free(data->ast_current);
	data->ast_current = NULL;
	free_ast(data);
}

void	free_assignment_list(t_assignment *assignments)
{
	t_assignment	*tmp;
	t_assignment	*tmp_to_free;

	if (assignments == NULL)
		return ;
	tmp = assignments;
	tmp_to_free = tmp;
	while (tmp)
	{
		tmp = tmp->next;
		free(tmp_to_free);
		tmp_to_free = tmp;
	}
	assignments = NULL;
}

void	free_redirect_list(t_redirect *io_redirect)
{
	t_redirect	*tmp;
	t_redirect	*tmp_to_free;

	if (io_redirect == NULL)
		return ;
	tmp = io_redirect;
	tmp_to_free = tmp;
	while (tmp)
	{
		tmp = tmp->next;
		free(tmp_to_free);
		tmp_to_free = tmp;
	}
	io_redirect = NULL;
}

void	free_ast_content(t_ast_content *content)
{
	free_redirect_list(content->stdin_redirect);
	free_redirect_list(content->stdout_redirect);
	free_assignment_list(content->assignments);
	free_str_arr(content->cmd);
	content = NULL;
}

void	free_str_arr(char **arr)
{
	int	i;

	i = 0;
	while (arr[i] != 0)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
	arr = NULL;
}

void	free_p(char	*p)
{
	if (p)
		free(p);
	p = NULL;
}
