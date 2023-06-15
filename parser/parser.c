/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunskim <eunskim@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 17:48:02 by eunskim           #+#    #+#             */
/*   Updated: 2023/06/15 20:45:12 by eunskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parser.h"

t_parser_exit_code	parse_command(t_parser *data, t_token_scanner *scanner)
{
	t_parser_exit_code	ret;
	t_ast				*cmd_node;
	t_ast_content		cmd_content;

	cmd_node = (t_ast *) ft_calloc(1, sizeof(t_ast));
	if (cmd_node == NULL)
	{
		data->malloc_failed = true;
		return (PARSER_FAILURE);
	}
	cmd_node->content = &cmd_content;
	add_new_ast_node_cmd(data, cmd_node);
	ret = parse_cmd_prefix(data, scanner, cmd_node);
	if (ret == PARSER_FAILURE)
	{
		ret = parse_cmd_word(data, scanner, cmd_node);
		if (ret == PARSER_FAILURE)
			return (ret);
	}
	else
	{
		if (parse_cmd_word(data, scanner) == PARSER_FAILURE)
			return (ret);
	}
	parse_cmd_suffix(data, scanner, cmd_node);
	return (ret);
}

t_parser_exit_code	parse_complete_command(t_parser *data, t_token_scanner *scanner)
{
	if (parse_command(data, scanner) == PARSER_FAILURE)
		return (PARSER_FAILURE);
	if (token_list_is_at_end(scanner) == true)
		return (PARSER_SUCCESS);
	if (parse_pipe(data, scanner) == PARSER_FAILURE)
		return (PARSER_FAILURE);
	if (parse_complete_command(data, scanner) == PARSER_FAILURE)
		return (PARSER_FAILURE);
	return (PARSER_SUCCESS);
}

t_parser_exit_code	parser(t_token_list *head)
{
	t_parser			data; // should be given as a parameter later
	t_token_scanner		scanner;
	t_parser_exit_code	parser_ret;

	if (head->token.type == TOKEN_EOF)
	{
		// free token list
		return (PARSER_FAILURE);
	}
	init_token_scanner(&scanner, head);
	init_parser_data(&data, &scanner);
	parser_ret = parse_complete_command(&data, &scanner);
	// free token list
	if (data.malloc_failed == true)
	{
		// free tree
		return (PARSER_FAILURE);
	}
	if (parser_ret == PARSER_FAILURE)
	{
		// free tree
		// print syntax error message
		return (PARSER_FAILURE);
	}
	return (PARSER_SUCCESS);
}
