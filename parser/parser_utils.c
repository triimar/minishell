/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunskim <eunskim@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 18:40:52 by eunskim           #+#    #+#             */
/*   Updated: 2023/06/13 18:58:23 by eunskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parser.h"

void	init_token_scanner(t_token_scanner *scanner, t_token_list *head)
{
	scanner->token_head = head;
	scanner->token_current = head;
}

void	init_parser_data(t_parser *data, t_token_scanner *scanner)
{
	data->ast_root = NULL;
	data->ast_current = NULL;
	data->malloc_failed = false;
	data->scanner = scanner;
}
