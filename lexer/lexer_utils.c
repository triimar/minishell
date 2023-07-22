/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunskim <eunskim@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 14:34:57 by eunskim           #+#    #+#             */
/*   Updated: 2023/07/22 20:14:07 by eunskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	lexer_error_printer(char *arg, char *msg)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	if (arg)
	{
		ft_putstr_fd(arg, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
	}
	ft_putendl_fd(msg, STDERR_FILENO);
}

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

void	init_lexer(t_lexer *data, t_scanner *scanner, const char *source)
{
	data->head = NULL;
	scanner->start = source;
	scanner->current = source;
}
