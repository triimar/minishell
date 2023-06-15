/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunskim <eunskim@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 14:58:24 by eunskim           #+#    #+#             */
/*   Updated: 2023/06/15 21:09:43 by eunskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "lexer.h"

typedef enum e_parser_exit_code
{
	PARSER_SUCCESS,
	PARSER_FAILURE
}	t_parser_exit_code;

typedef enum e_redirect_type
{
	REDIRECT_STDIN,
	REDIRECT_HERE_DOC,
	REDIRECT_STDOUT,
	REDIRECT_STDOUT_APPEND
}	t_redirect_type;

typedef struct s_redirect
{
	t_redirect_type	type;
	char			*word;
	t_redirect		*next;
}	t_redirect;

typedef struct s_assignment
{
	char			*word;
	t_assignment	*next;
}	t_assignment;

typedef struct s_ast_content
{
	t_redirect		*stdin_redirect;
	t_redirect		*stdout_redirect;
	t_assignment	*assignments;
	char			**cmd;
}	t_ast_content;

typedef struct s_ast
{
	t_ast_content	*content;
	t_ast			*left;
	t_ast			*right;
}	t_ast;

typedef struct s_token_scanner
{
	t_token_list		*token_head;
	t_token_list		*token_current;
}	t_token_scanner;

typedef struct s_parser
{
	t_ast				*ast_root;
	t_ast				*ast_current;
	bool				malloc_failed;
	t_token_scanner		*scanner;
}	t_parser;

#endif