/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunskim <eunskim@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 18:30:53 by eunskim           #+#    #+#             */
/*   Updated: 2023/06/16 13:30:03 by eunskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parser.h"

// possible cases for new pipe node
// 1) root != null, content != null -> pipe node should be the root
// 2) root != null, content != null -> anyway pipe node should be the root
// current root should be the left node of the root

void	add_new_ast_node_pipe(t_parser *data, t_ast *cmd_node)
{
	cmd_node->left = data->ast_root;
	data->ast_root = cmd_node;
}

// possible cases for new cmd node
// 1) root = null -> new node should be the root
// 2) root != null, content = null (is a pipe)
// root->right should be null, add new cmd node here

void	add_new_ast_node_cmd(t_parser *data, t_ast *cmd_node)
{
	if (data->ast_root == NULL)
		data->ast_root = cmd_node;
	if (data->ast_root != NULL && data->ast_root->content == NULL)
		data->ast_root->right = cmd_node;
}
