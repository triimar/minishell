/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunskim <eunskim@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 19:08:11 by eunskim           #+#    #+#             */
/*   Updated: 2023/07/22 19:40:50 by eunskim          ###   ########.fr       */
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
				return (make_error_token("syntax error unclosed quote"));
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

t_lexer_exit_code	lexer(t_lexer *data, const char *source)
{
	t_scanner		scanner;
	t_token			token;
	t_token_list	*tmp_token_node;

	init_lexer(data, &scanner, source);
	while (true)
	{
		token = scan_token(&scanner);
		if (token.type == TOKEN_ERROR)
		{
			lexer_error_printer(NULL, (char *) token.start);
			return (free_token_list(data), UNCLOSED_QUOTE);
		}
		tmp_token_node = make_token_node(token);
		if (tmp_token_node == NULL)
		{
			lexer_error_printer("internal error", "Malloc failed");
			return (free_token_list(data), MALLOC_ERROR);
		}
		add_token_node_back(&data->head, tmp_token_node);
		if (token.type == TOKEN_EOF)
			break ;
	}
	iter_token_list(data, &check_if_assignment_word);
	return (LEXER_SUCCESS);
}
