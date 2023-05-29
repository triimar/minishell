/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunskim <eunskim@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 19:08:11 by eunskim           #+#    #+#             */
/*   Updated: 2023/05/29 16:27:46 by eunskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "lexer.h"
#include "../include/lexer.h"

// void	check_if_assignment_word(t_token *token)
// {
// 	char	*equal_sign;
// 	char	*word;

// 	if (token->type != TOKEN_WORD)
// 		return ;
// 	else
// 	{
// 		// word = ft_strdup();
// 		// equal_sign = ft_strchr();
// 	}
// }

t_token	scan_word(t_scanner *scanner, char c)
{
	char	quote;
	int		quote_cnt;

	quote_cnt = 0;
	while (ft_strchr(WHITESPACES, c) == 0 && c != '\0')
	{
		if (ft_strchr(QUOTES, c) != 0)
		{
			quote = c;
			quote_cnt++;
			c = advance(scanner);
			while (ft_strchr(WHITESPACES, c) == 0 && c != '\0')
			{
				if (c == quote)
				{
					quote_cnt++;
					break;
				}
				c = advance(scanner);
			}
		}
		c = advance(scanner);
	}
	if (quote_cnt % 2 == 0)
		return (make_token(TOKEN_WORD, scanner));
	else
		return (make_error_token("syntax error unclosed quote"));
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
	else
		return (scan_word(scanner, c));
}

t_lexer_exit_code	lexer(const char *source)
{
	t_lexer			data; // should be given as a parameter later
	t_scanner		scanner;
	t_token			*token;
	t_token_list	*tmp_token_node;

	init_lexer_data(&data);
	init_scanner(&scanner, source);
	while (true)
	{
		*token = scan_token(&scanner);
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
		if (token.type == TOKEN_ERROR)
		{
			ft_putstr_fd(token.start, 2); // need to be edited later
			free_token_list(&data);
			return (UNCLOSED_QUOTE);
		}
	}
	// iter_token_list(&data, check_if_assignment_word);
	lexer_test(&data); // printing and freeing for testing
	return (LEXER_SUCCESS);
}
