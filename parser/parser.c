/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunskim <eunskim@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 17:48:02 by eunskim           #+#    #+#             */
/*   Updated: 2023/06/09 22:24:10 by eunskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parser.h"

t_parser_exit_code	parse_cmd_prefix(t_parser *data, t_token_scanner *scanner)
{
	t_parser_exit_code	ret;

	ret = PARSER_FAILURE;
	while (true)
	{
		if (peek_token(scanner) == TOKEN_GREAT \
		|| peek_token(scanner) == TOKEN_DGREAT \
		|| peek_token(scanner) == TOKEN_LESS \
		|| peek_token(scanner) == TOKEN_DLESS)
		{
			if (peek_next_token(scanner) == TOKEN_WORD \
			|| peek_next_token(scanner) == TOKEN_ASSIGNMENT_WORD)
			{
				// add redirection (advance twice)
				ret = PARSER_SUCCESS;
				continue;
			}
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

t_parser_exit_code	parse_command(t_parser *data, t_token_scanner *scanner)
{
	t_parser_exit_code	ret;

	ret = parse_cmd_prefix(data, scanner);
	if (ret == PARSER_FAILURE)
	{
		ret = parse_cmd_word(data, scanner);
		if (ret == PARSER_FAILURE)
			return (ret);
	}
	else
	{
		if (parse_cmd_word(data, scanner) == PARSER_FAILURE)
			return (ret);
	}
	parse_cmd_suffix(data);
	return (ret);
}

t_parser_exit_code	parse_complete_command(t_parser *data, t_token_scanner *scanner)
{
	if (parse_command(data, scanner) == PARSER_FAILURE)
		return (PARSER_FAILURE);
	if (parse_EOF(data, scanner) == PARSER_SUCCESS)
		return (PARSER_SUCCESS);
	if (parse_pipe(data, scanner) == PARSER_FAILURE)
		return (PARSER_FAILURE);
	if (parse_complete_command(data, scanner) == PARSER_FAILURE)
		return (PARSER_FAILURE);
	return (PARSER_SUCCESS);
}
