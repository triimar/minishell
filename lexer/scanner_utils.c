/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scanner_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunskim <eunskim@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 14:35:52 by eunskim           #+#    #+#             */
/*   Updated: 2023/05/29 14:39:12 by eunskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "lexer.h"
#include "../include/lexer.h"

char	advance(t_scanner *scanner)
{
	char	c;

	c = *scanner->current;
	scanner->current++;
	return (c);
}

void	init_scanner(t_scanner *scanner, const char *source)
{
	scanner->start = source;
	scanner->current = source;
}