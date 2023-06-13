/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunskim <eunskim@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 17:48:02 by eunskim           #+#    #+#             */
/*   Updated: 2023/06/13 17:23:31 by eunskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parser.h"

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
	parse_cmd_suffix(data, scanner);
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
