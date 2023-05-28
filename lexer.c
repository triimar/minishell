/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunskim <eunskim@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 19:08:11 by eunskim           #+#    #+#             */
/*   Updated: 2023/05/28 21:20:56 by eunskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

// peek, peek_next, match

bool	check_if_assignment_word()
{
	
}

t_token	scan_word(t_scanner scanner, char c)
{
	
}

t_token make_error_token(const char *message)
{
	t_token token;

	token.type = TOKEN_ERROR;
	token.start = message;
	token.length = (int) ft_strlen(message);
	return (token);
}

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

t_token	scan_redirections(t_scanner scanner, char c)
{
	if (c == '>')
	{
		if (*(scanner.current + 1) != '>')
			return (make_token(TOKEN_GREAT, scanner));
		else
		{
			scanner.current++;
			return (make_token(TOKEN_DGREAT, scanner));
		}
	}
	else
	{
		if (*(scanner.current + 1) != '<')
			return (make_token(TOKEN_LESS, scanner));
		else
		{
			scanner.current++;
			return (make_token(TOKEN_DLESS, scanner));
		}
	}
}

t_token	make_token(t_token_type type, t_scanner scanner)
{
	t_token	token;

	token.type = type;
	token.start = scanner.start;
	token.length = scanner.current - scanner.start;
	return (token);
}

char	advance(t_scanner scanner)
{
	c = *scanner.current;
	scanner.current++;
	return (c);
}

t_token	scan_token(t_scanner scanner)
{
	char	c;

	scanner.start = scanner.current;
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

int	lexer(const char *source)
{
	t_lexer			data;
	t_scanner		scanner;
	t_token			token;
	t_token_list	tmp_node;

	init_lexer_data(data);
	init_scanner(scanner, source);
	while (true)
	{
		token = scan_token()
		tmp_token_node = make_token_node(token);
		if (tmp_node == NULL)
		{
			free_token_list(data);
			return (-1); // malloc error in lexer
		}
		add_token_node(data, tmp_token_node);
		update_lexer_data(data, tmp_token_node)
		if (token.type == TOKEN_EOF)
			break;
		if (token.type == TOKEN_ERROR)
		{
			ft_putstr_fd(token.start, 2); // need to be edited later
			free_token_list(data);
			return (-2) // unclosed quote error during lexing
		}
	}
	return (0);
}
