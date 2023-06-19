/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_scanner_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunskim <eunskim@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 20:15:24 by eunskim           #+#    #+#             */
/*   Updated: 2023/06/19 15:43:26 by eunskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

bool	token_is_redirection(t_token_scanner *scanner)
{
	if (peek_token(scanner) == TOKEN_GREAT \
	|| peek_token(scanner) == TOKEN_DGREAT \
	|| peek_token(scanner) == TOKEN_LESS \
	|| peek_token(scanner) == TOKEN_DLESS)
		return (true);
	return (false);
}

t_token_type	peek_next_token(t_token_scanner *scanner)
{
	return (scanner->token_current->next->token.type);
}

t_token_type	peek_token(t_token_scanner *scanner)
{
	return (scanner->token_current->token.type);
}

bool	token_list_is_at_end(t_token_scanner *scanner)
{
	if (scanner->token_current->token.type == TOKEN_EOF)
		return (true);
	return (false);
}

void	advance_token_list(t_token_scanner *scanner)
{
	scanner->token_current = scanner->token_current->next;
}