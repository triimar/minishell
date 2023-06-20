/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunskim <eunskim@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 17:48:02 by eunskim           #+#    #+#             */
/*   Updated: 2023/06/20 15:17:18 by eunskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_parser_exit_code	parse_command(t_parser *data, t_token_scanner *scanner)
{
	t_parser_exit_code	ret;
	t_ast				*cmd_node;

	cmd_node = (t_ast *) ft_calloc(1, sizeof(t_ast));
	if (cmd_node == NULL)
	{
		data->malloc_failed = true;
		return (PARSER_FAILURE);
	}
	cmd_node->content = (t_ast_content *) ft_calloc(1, sizeof(t_ast_content));
	if (cmd_node->content == NULL)
	{
		free(cmd_node);
		data->malloc_failed = true;
		return (PARSER_FAILURE);
	}
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
		if (parse_cmd_word(data, scanner, cmd_node) == PARSER_FAILURE)
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

t_parser_exit_code	parser(t_parser *data, t_lexer *lexer_data)
{
	t_token_scanner		scanner;
	t_parser_exit_code	parser_ret;

	if (lexer_data->head->token.type == TOKEN_EOF)
	{
		free_token_list(lexer_data);
		return (PARSER_FAILURE);
	}
	init_token_scanner(&scanner, lexer_data->head);
	init_parser_data(data, &scanner);
	parser_ret = parse_complete_command(data, &scanner);
	free_token_list(lexer_data);
	if (data->malloc_failed == true)
	{
		ft_putstr_fd("malloc failed", 2);
		free_ast(data);
		return (PARSER_FAILURE);
	}
	if (parser_ret == PARSER_FAILURE)
	{
		ft_putstr_fd("syntax error", 2);
		// print_ast(data);
		free_ast(data);
		return (PARSER_FAILURE); 
	}
	return (PARSER_SUCCESS);
}

int	main(int argc, char **argv)
{
	t_lexer		lexer_data;
	t_parser	parser_data;

	if (argc != 2)
		return (EXIT_FAILURE);
	if (lexer(&lexer_data, argv[1]) != LEXER_SUCCESS)
		return (EXIT_FAILURE);
	if (parser(&parser_data, &lexer_data) == PARSER_FAILURE)
		return (EXIT_FAILURE);
	parser_test(&parser_data); // testing and freeing
	return (EXIT_SUCCESS);
}