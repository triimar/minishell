/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scanner_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunskim <eunskim@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 14:35:52 by eunskim           #+#    #+#             */
/*   Updated: 2023/06/01 18:19:19 by eunskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

char	peek(t_scanner *scanner)
{
	return (*scanner->current);
}

bool	match(t_scanner *scanner, char expected)
{
	if (is_at_end(scanner) || *scanner->current != expected)
		return (false);
	scanner->current++;
	return (true);
}

bool	is_at_end(t_scanner *scanner)
{
	if (*scanner->current == '\0')
		return (true);
	else
		return (false);
}

void	skip_whitespaces(t_scanner *scanner)
{
	while (ft_strchr(WHITESPACES, peek(scanner)) != 0 && !is_at_end(scanner))
		advance(scanner);
}

char	advance(t_scanner *scanner)
{
	char	c;

	c = *scanner->current;
	if (c != '\0')
		scanner->current++;
	return (c);
}
