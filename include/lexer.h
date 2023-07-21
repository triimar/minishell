/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunskim <eunskim@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 19:08:02 by eunskim           #+#    #+#             */
/*   Updated: 2023/07/19 18:29:06 by eunskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <stdbool.h>
# include "libft.h"

# define WHITESPACES " \t\v\f\r"
# define WORD_DELIMITER " \t\v\f\r><|"

typedef enum e_lexer_exit_code
{
	LEXER_SUCCESS,
	INVALID_ARGUMENT,
	NOTHING_TO_SCAN,
	UNCLOSED_QUOTE,
	MALLOC_ERROR
}	t_lexer_exit_code;

typedef enum e_token_type
{
	TOKEN_EOF,
	TOKEN_WORD,
	TOKEN_ASSIGNMENT_WORD,
	TOKEN_GREAT,
	TOKEN_DGREAT,
	TOKEN_LESS,
	TOKEN_DLESS,
	TOKEN_PIPE,
	TOKEN_ERROR
}	t_token_type;

typedef struct s_scanner
{
	const char	*start;
	const char	*current;
}	t_scanner;

typedef struct s_token
{
	t_token_type	type;
	const char		*start;
	int				length;
}	t_token;

typedef struct s_token_list	t_token_list;

typedef struct s_token_list
{
	t_token			token;
	t_token_list	*next;
}	t_token_list;

typedef struct s_lexer
{
	t_token_list	*head;
}	t_lexer;

/* lexer.c */
t_lexer_exit_code	lexer(t_lexer *data, const char *source);
t_token				scan_token(t_scanner *scanner);
t_token				scan_redirections(t_scanner *scanner, char c);
t_token				scan_word(t_scanner *scanner, char c);
void				check_if_assignment_word(t_token *token);

/* lexer_utils.c */
void				init_lexer_data(t_lexer *data);
void				init_scanner(t_scanner *scanner, const char *source);
t_token				make_token(t_token_type type, t_scanner *scanner);
t_token				make_error_token(const char *message);

/* scanner_utils.c */
char				advance(t_scanner *scanner);
void				skip_whitespaces(t_scanner *scanner);
bool				is_at_end(t_scanner *scanner);
bool				match(t_scanner *scanner, char expected);
char				peek(t_scanner *scanner);

/* token_list_utils */
t_token_list		*make_token_node(t_token token);
void				add_token_node_back(t_token_list **head, t_token_list *new);
void				free_token_list(t_lexer *data);
void				iter_token_list(t_lexer *data, void (*f)(t_token *));

/* for_test.c */
void				lexer_test(t_lexer *data);
void				print_token(t_token_list *token_head);

#endif