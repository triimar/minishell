/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_test.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunskim <eunskim@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 15:43:34 by eunskim           #+#    #+#             */
/*   Updated: 2023/06/19 16:02:29 by eunskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	print_ast(data)
{
	
}

void	parser_test(t_parser *data)
{
	print_ast(data);
	free_ast(data);
	clean_parser_data(data);
}