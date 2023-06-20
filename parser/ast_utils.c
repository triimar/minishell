/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunskim <eunskim@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 18:30:53 by eunskim           #+#    #+#             */
/*   Updated: 2023/06/20 19:45:08 by eunskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	add_new_ast_node_pipe(t_parser *data, t_ast *cmd_node)
{
	cmd_node->left = data->ast_root;
	data->ast_root = cmd_node;
}

void	add_new_ast_node_cmd(t_parser *data, t_ast *cmd_node)
{
	if (data->ast_root == NULL)
		data->ast_root = cmd_node;
	if (data->ast_root != NULL && data->ast_root->content == NULL)
		data->ast_root->right = cmd_node;
}
