/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_test.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarts <tmarts@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 15:43:34 by eunskim           #+#    #+#             */
/*   Updated: 2023/07/12 19:08:44 by tmarts           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

typedef enum e_branch {
	LEFT,
	RIGHT
}	t_branch;

// static t_ast	*from_identifier_to_tree(t_ast *node, t_branch branch)
// {
// 	if (branch == LEFT)
// 		return (node->left);
// 	else
// 		return (node->right);
// }

// static void	print_ast_content(t_ast_content *content)
// {
// 	t_redirect		*tmp_redirect;
// 	t_assignment	*tmp_assignment;

// 	if (content == NULL)
// 	{
// 		printf("     .");
// 		printf("\n>> Ceci n'est pas une pipe. <<\n");
// 		return ;
// 	}
// 	printf("\n>> This is a command node. <<\n");

// 	int i = 1;
// 	tmp_redirect = content->stdin_redirect;
// 	while (tmp_redirect)
// 	{
// 		printf("stdin redirect #%d type: %d, word: %s\n", i, tmp_redirect->type, tmp_redirect->word);
// 		tmp_redirect = tmp_redirect->next;
// 		i++;
// 	}
// 	i = 1;
// 	tmp_redirect = content->stdout_redirect;
// 	while (tmp_redirect)
// 	{
// 		printf("stdout redirect #%d type: %d, word: %s\n", i, tmp_redirect->type, tmp_redirect->word);
// 		tmp_redirect = tmp_redirect->next;
// 		i++;
// 	}
// 	i = 1;
// 	tmp_assignment = content->assignments;
// 	while (tmp_assignment)
// 	{
// 		printf("assignment word #%d: %s\n", i, tmp_assignment->word);
// 		tmp_assignment = tmp_assignment->next;
// 		i++;
// 	}
// 	if (content->cmd == NULL)
// 		return ;
// 	if (content->cmd[0] != NULL)
// 		printf("cmd word: %s\n", content->cmd[0]);
// 	for (i = 1; content->cmd[i] != NULL; i++)
// 	{
// 		printf("cmd arg #%d: ", i);
// 		printf("%s\n", content->cmd[i]);	
// 	}
// }
// static void	print_ast_recursive(t_ast *node, int level, t_branch branch)
// {
// 	if (node == NULL)
// 		return ;

// 	int i = 0;
// 	// print the right subtree
// 	print_ast_recursive(from_identifier_to_tree(node, branch), level + 1, branch);
// 	// print the current node
// 	while (i < level)
// 	{
// 		printf("     .");
// 		i++;
// 	}
// 	print_ast_content(node->content);
// 	printf("\n");
// 	// print the left subtree
// 	print_ast_recursive(from_identifier_to_tree(node, !branch), level + 1, branch);
// }

// static void	print_ast(t_ast *ast_root)
// {
// 	printf("\n------- Abstract Syntax Tree -------\n\n");
// 	if (ast_root == NULL)
// 		printf("... no content\n");
// 	print_ast_recursive(ast_root, 0, LEFT);
// 	printf("------------------------------------------\n");
// }

void	parser_test(t_parser *data)
{
	// print_ast(data->ast_root);
	free_ast(data); 
}