/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_free.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunskim <eunskim@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 12:53:09 by eunskim           #+#    #+#             */
/*   Updated: 2023/07/22 20:32:13 by eunskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	parser_free(t_parser *data, t_lexer *lexer_data)
{
	free_ast(data);
	free_token_list(lexer_data);
}

void	free_ast_content(t_ast_content *content)
{
	free_redirect_list(&content->stdin_redirect);
	free_redirect_list(&content->stdout_redirect);
	free_assignment_list(content);
	free_str_arr(content->cmd);
	free(content);
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

void	free_str_arr(char **arr)
{
	int	i;

	i = 0;
	if (arr == NULL || *arr == NULL)
		return ;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

void	free_p(char	*p)
{
	if (p)
		free(p);
}
