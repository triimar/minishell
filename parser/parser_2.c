/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunskim <eunskim@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 15:58:04 by eunskim           #+#    #+#             */
/*   Updated: 2023/06/13 17:23:22 by eunskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parser.h"

t_parser_exit_code	parse_pipe(t_parser *data, t_token_scanner *scanner)
{
	if (peek_token(scanner) == TOKEN_PIPE)
	{
		// add pipe (advance once)
		return (PARSER_SUCCESS);
	}
	else
		return (PARSER_FAILURE);
}

t_parser_exit_code	parse_redirection(t_parser *data, t_token_scanner *scanner)
{
	if (peek_token(scanner) == TOKEN_GREAT \
	|| peek_token(scanner) == TOKEN_DGREAT)
		// add stdout redirection (advance twice)
	else if (peek_token(scanner) == TOKEN_LESS \
	|| peek_token(scanner) == TOKEN_DLESS)
		// add stdin redirection (advance twice)
	return (PARSER_SUCCESS);
}

t_parser_exit_code	parse_cmd_suffix(t_parser *data, t_token_scanner *scanner)
{
	t_parser_exit_code	ret;

	ret = PARSER_FAILURE;
	while (true)
	{
		if (token_is_redirection(scanner) == true)
		{
			if (peek_next_token(scanner) == TOKEN_WORD \
			|| peek_next_token(scanner) == TOKEN_ASSIGNMENT_WORD)
				ret = parse_redirection(data, scanner);
			else
				break;
		}
		else if (peek_token(scanner) == TOKEN_WORD \
		|| peek_token(scanner) == TOKEN_ASSIGNMENT_WORD)
		{
			// add cmd arg (advance once)
			ret = PARSER_SUCCESS;
			continue;
		}
		else
			break;
	}
	return (ret);
}

t_parser_exit_code	parse_cmd_word(t_parser *data, t_token_scanner *scanner)
{
	if (peek_token(scanner) == TOKEN_WORD)
	{
		// add cmd word (advance once)
		return (PARSER_SUCCESS);
	}
	else
		return (PARSER_FAILURE);
}

t_parser_exit_code	parse_cmd_prefix(t_parser *data, t_token_scanner *scanner)
{
	t_parser_exit_code	ret;

	ret = PARSER_FAILURE;
	while (true)
	{
		if (token_is_redirection(scanner) == true)
		{
			if (peek_next_token(scanner) == TOKEN_WORD \
			|| peek_next_token(scanner) == TOKEN_ASSIGNMENT_WORD)
				ret = parse_redirection(data, scanner);
			else
				break;
		}
		else if (peek_token(scanner) == TOKEN_ASSIGNMENT_WORD)
		{
			// add assignment word (advance once)
			ret = PARSER_SUCCESS;
			continue;
		}
		else
			break;
	}
	return (ret);
}
