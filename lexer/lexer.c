/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunskim <eunskim@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 19:08:11 by eunskim           #+#    #+#             */
/*   Updated: 2023/05/29 14:40:55 by eunskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "lexer.h"
#include "../include/lexer.h"

// peek, peek_next, match

bool	check_if_assignment_word()
{
	
}

t_token	scan_word(t_scanner scanner, char c)
{
	
}

// error check function
// if (token.type == TOKEN_ERROR)
// {
// 	ft_putstr_fd(token.start, 2); // need to be edited later
// 	free_token_list(&data);
// 	return (UNCLOSED_QUOTE); // unclosed quote error during lexing
// }

t_token scan_quoted_word(t_scanner scanner, char c)
{
	if (c == '\"')
	{
		c = advance(scanner);
		while (c != '\0' || c == '\"')
			c = advance(scanner);
		if (c == '\"')
			return (make_token(TOKEN_WORD, scanner));	
	}
	else
	{
		c = advance(scanner);
		while (c != '\0' || c == '\'')
			c = advance(scanner);
		if (c == '\'')
			return (make_token(TOKEN_WORD, scanner));
	}
	return (make_error_token("unclosed quote syntax error")); // should be edited later
}

t_token	scan_redirections(t_scanner *scanner, char c)
{
	if (c == '>')
	{
		if (*(scanner->current + 1) != '>')
			return (make_token(TOKEN_GREAT, scanner));
		else
		{
			scanner->current++;
			return (make_token(TOKEN_DGREAT, scanner));
		}
	}
	else
	{
		if (*(scanner->current + 1) != '<')
			return (make_token(TOKEN_LESS, scanner));
		else
		{
			scanner->current++;
			return (make_token(TOKEN_DLESS, scanner));
		}
	}
}

t_token	scan_token(t_scanner *scanner)
{
	char	c;

	scanner->start = scanner->current;
	c = advance(scanner);
	while (ft_strchr(WHITESPACES, c) != 0)
		c = advance(scanner);
	if (c == '\0')
		return (make_token(TOKEN_EOF, scanner));
	else if (c == '|')
		return (make_token(TOKEN_PIPE, scanner));
	else if (ft_strchr(REDIRECTIONS, c) != 0)
		return (scan_redirection(scanner, c));
	else if (ft_strchr(QUOTES, c) != 0)
		return (scan_quoted_word(scanner, c));
	else
		return (scan_word(scanner, c));
}

t_lexer_exit_code	lexer(const char *source)
{
	t_lexer			data;
	t_scanner		scanner;
	t_token			token;
	t_token_list	*tmp_token_node;

	init_lexer_data(&data);
	init_scanner(&scanner, source);
	while (true)
	{
		token = scan_token(&scanner);
		tmp_token_node = make_token_node(token);
		if (tmp_token_node == NULL)
		{
			free_token_list(&data);
			return (MALLOC_ERROR);
		}
		add_token_node_back(&data.head, tmp_token_node);
		update_lexer_data(&data, tmp_token_node);
		if (token.type == TOKEN_EOF)
			break;
	}
	// error checker
	// assignment_word checker
	return (0);
}
