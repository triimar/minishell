/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunskim <eunskim@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 19:08:11 by eunskim           #+#    #+#             */
/*   Updated: 2023/06/02 15:56:33 by eunskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	check_if_assignment_word(t_token *token)
{
	int			i;
	const char	*word;

	i = 0;
	if (token->type != TOKEN_WORD)
		return ;
	else
	{
		word = token->start;
		if (!ft_isalpha(*word) && *word != '_')
			return ;
		while (++i < token->length && word[i] != '=')
		{
			if (!ft_isalpha(word[i]) && word[i] != '_' && !ft_isdigit(word[i]))
				return ;
		}
		if (word[i] == '=')
			token->type = TOKEN_ASSIGNMENT_WORD;
	}
}

t_token	scan_word(t_scanner *scanner, char c)
{
	char	quote;

	quote = c;
	while (true)
	{
		if (quote == '\"' || quote == '\'')
		{
			while (peek(scanner) != quote && !is_at_end(scanner))
				advance(scanner);
			if (is_at_end(scanner))
				return (make_error_token("syntax error unclosed quote\n"));
			advance(scanner);
			if (ft_strchr(WORD_DELIMITER, peek(scanner)) != 0)
				return (make_token(TOKEN_WORD, scanner));
			quote = advance(scanner);		
		}
		else
		{
			if (ft_strchr(WORD_DELIMITER, peek(scanner)) != 0)
				return (make_token(TOKEN_WORD, scanner));
			quote = advance(scanner);
		}
	}
}

t_token	scan_redirections(t_scanner *scanner, char c)
{
	if (c == '>')
	{
		if (match(scanner, '>'))
			return (make_token(TOKEN_DGREAT, scanner));
		else
			return (make_token(TOKEN_GREAT, scanner));
	}
	else
	{
		if (match(scanner, '<'))
			return (make_token(TOKEN_DLESS, scanner));
		else
			return (make_token(TOKEN_LESS, scanner));
	}
}

t_token	scan_token(t_scanner *scanner)
{
	char	c;

	skip_whitespaces(scanner);
	scanner->start = scanner->current;
	if (is_at_end(scanner))
		return (make_token(TOKEN_EOF, scanner));
	c = advance(scanner);
	if (c == '|')
		return (make_token(TOKEN_PIPE, scanner));
	else if (c == '>' || c == '<')
		return (scan_redirections(scanner, c));
	else
		return (scan_word(scanner, c));
}

t_lexer_exit_code	lexer(const char *source)
{
	t_lexer			data; // should be given as a parameter later
	t_scanner		scanner;
	t_token			token;
	t_token_list	*tmp_token_node;

	if (!source)
		return (NOTHING_TO_SCAN);
	init_lexer_data(&data);
	init_scanner(&scanner, source);
	while (true)
	{
		token = scan_token(&scanner);
		if (token.type == TOKEN_EOF)
			break ;
		if (token.type == TOKEN_ERROR)
		{
			ft_putstr_fd((char *) token.start, 2); // need to be edited later
			free_token_list(&data);
			return (UNCLOSED_QUOTE);
		}
		tmp_token_node = make_token_node(token);
		if (tmp_token_node == NULL)
		{
			free_token_list(&data);
			return (MALLOC_ERROR);
		}
		add_token_node_back(&data.head, tmp_token_node);
	}
	iter_token_list(&data, &check_if_assignment_word);
	lexer_test(&data); // printing and freeing for testing
	// system("leaks lexer");
	return (LEXER_SUCCESS);
}
