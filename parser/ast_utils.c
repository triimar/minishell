/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunskim <eunskim@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 18:30:53 by eunskim           #+#    #+#             */
/*   Updated: 2023/06/15 17:56:44 by eunskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parser.h"

// function add_new_ast_node_cmd

// possible cases
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
