/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_subfunc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunskim <eunskim@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 15:58:04 by eunskim           #+#    #+#             */
/*   Updated: 2023/06/23 14:21:24 by eunskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static t_parser_exit_code	parse_redirection(t_parser *data, \
t_token_scanner *scanner, t_ast *cmd_node)
{
	if (peek_token(scanner) == TOKEN_LESS)
		return (add_redirection(data, scanner, cmd_node, REDIRECT_STDIN));
	else if (peek_token(scanner) == TOKEN_DLESS)
		return (add_redirection(data, scanner, cmd_node, REDIRECT_HERE_DOC));
	else if (peek_token(scanner) == TOKEN_GREAT)
		return (add_redirection(data, scanner, cmd_node, REDIRECT_STDOUT));
	else if (peek_token(scanner) == TOKEN_DGREAT)
		return (add_redirection(data, scanner, cmd_node, \
		REDIRECT_STDOUT_APPEND));
	return (PARSER_FAILURE);
}

t_parser_exit_code	parse_cmd_suffix(t_parser *data, \
t_token_scanner *scanner, t_ast *cmd_node)
{
	t_parser_exit_code	ret;

	ret = PARSER_FAILURE;
	while (true)
	{
		if (data->malloc_failed == true)
			return (PARSER_FAILURE);
		if (token_is_redirection(scanner) == true \
		&& (peek_next_token(scanner) == TOKEN_WORD \
		|| peek_next_token(scanner) == TOKEN_ASSIGNMENT_WORD))
		{
			ret = parse_redirection(data, scanner, cmd_node);
			continue ;
		}
		else if (peek_token(scanner) == TOKEN_WORD \
		|| peek_token(scanner) == TOKEN_ASSIGNMENT_WORD)
		{
			ret = add_cmd_and_cmd_args(data, scanner, cmd_node);
			continue ;
		}
		else
			break ;
	}
	return (ret);
}

t_parser_exit_code	parse_cmd_word(t_parser *data, \
t_token_scanner *scanner, t_ast *cmd_node)
{
	if (data->malloc_failed == true)
		return (PARSER_FAILURE);
	if (peek_token(scanner) == TOKEN_WORD)
	{
		add_cmd_and_cmd_args(data, scanner, cmd_node);
		return (PARSER_SUCCESS);
	}
	else
		return (PARSER_FAILURE);
}

t_parser_exit_code	parse_cmd_prefix(t_parser *data, \
t_token_scanner *scanner, t_ast *cmd_node)
{
	t_parser_exit_code	ret;

	ret = PARSER_FAILURE;
	while (true)
	{
		if (data->malloc_failed == true)
			return (PARSER_FAILURE);
		if (token_is_redirection(scanner) == true \
		&& (peek_next_token(scanner) == TOKEN_WORD \
		|| peek_next_token(scanner) == TOKEN_ASSIGNMENT_WORD))
		{
			ret = parse_redirection(data, scanner, cmd_node);
			continue ;
		}
		else if (peek_token(scanner) == TOKEN_ASSIGNMENT_WORD)
		{
			ret = add_assignment_word(data, scanner, cmd_node);
			continue ;
		}
		else
			break ;
	}
	return (ret);
}
