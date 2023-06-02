/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunskim <eunskim@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 14:34:57 by eunskim           #+#    #+#             */
/*   Updated: 2023/06/02 15:42:04 by eunskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

t_token	make_error_token(const char *message)
{
	t_token	token;

	token.type = TOKEN_ERROR;
	token.start = message;
	token.length = (int) ft_strlen(message);
	return (token);
}

t_token	make_token(t_token_type type, t_scanner *scanner)
{
	t_token	token;

	token.type = type;
	token.start = scanner->start;
	token.length = (int)(scanner->current - scanner->start);
	return (token);
}

void	init_scanner(t_scanner *scanner, const char *source)
{
	scanner->start = source;
	scanner->current = source;
}

void	init_lexer_data(t_lexer *data)
{
	data->head = NULL;
}
