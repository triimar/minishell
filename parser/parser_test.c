/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_test.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunskim <eunskim@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 15:43:34 by eunskim           #+#    #+#             */
/*   Updated: 2023/06/20 16:26:32 by eunskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	print_ast_content(t_ast_content *content)
{
	t_redirect		*tmp_redirect;
	t_assignment	*tmp_assignment;

	printf("\n>> This is a command node. <<\n");

	tmp_redirect = content->stdin_redirect;
	while (tmp_redirect)
	{
		printf("redirect type: %d, word: %s\n", tmp_redirect->type, tmp_redirect->word);
		tmp_redirect = tmp_redirect->next;
	}
	tmp_redirect = content->stdout_redirect;
	while (tmp_redirect)
	{
		printf("redirect type: %d, word: %s\n", tmp_redirect->type, tmp_redirect->word);
		tmp_redirect = tmp_redirect->next;
	}
	tmp_assignment = content->assignments;
	while (tmp_assignment)
	{
		printf("assignment word: %s\n", tmp_assignment->word);
		tmp_assignment = tmp_assignment->next;
	}
	if (content->cmd == NULL)
		return ;
	if (content->cmd[0] != NULL)
		printf("cmd word: %s\n", content->cmd[0]);
	for (int i = 1; content->cmd[i] != NULL; i++)
	{
		printf("cmd arg %d: ", i);
		printf("%s\n", content->cmd[i]);	
	}
}

void	print_ast(t_parser *data)
{
	if (data->ast_root == NULL)
		return ;
	data->ast_current = data->ast_root;
	if (data->ast_current->content == NULL)
	{
		printf("\n>> Ceci n'est pas une pipe. <<\n");
		if (data->ast_current->right != NULL)
			print_ast_content(data->ast_current->right->content);
	}
	else if (data->ast_current->content != NULL)
		print_ast_content(data->ast_current->content);
	data->ast_root = data->ast_current->left;
	print_ast(data);
}

void	parser_test(t_parser *data)
{
	print_ast(data);
	free_ast(data);
}