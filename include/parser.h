/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunskim <eunskim@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 14:58:24 by eunskim           #+#    #+#             */
/*   Updated: 2023/07/04 17:25:13 by eunskim          ###   ########.fr       */
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

typedef struct s_redirect	t_redirect;
typedef struct s_assignment	t_assignment;
typedef struct s_ast		t_ast;

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

/* parser.c */
t_parser_exit_code	parser(t_parser *data, const char *source);
t_parser_exit_code	parse_complete_command(t_parser *data, \
t_token_scanner *scanner);
t_parser_exit_code	parse_command(t_parser *data, t_token_scanner *scanner);
t_parser_exit_code	parse_pipe(t_parser *data, t_token_scanner *scanner);

/* parser_subfunc.c */
t_parser_exit_code	parse_cmd_prefix(t_parser *data, \
t_token_scanner *scanner, t_ast *cmd_node);
t_parser_exit_code	parse_cmd_word(t_parser *data, \
t_token_scanner *scanner, t_ast *cmd_node);
t_parser_exit_code	parse_cmd_suffix(t_parser *data, \
t_token_scanner *scanner, t_ast *cmd_node);

/* parser_utils.c */
void				init_token_scanner(t_token_scanner *scanner, \
t_token_list *head);
void				init_parser_data(t_parser *data, t_token_scanner *scanner);
char				*produce_dup_string(const char *start, int length);
char				**extend_string_array(char **param, int word_cnt);

/* token_scanner_utils.c */
void				advance_token_list(t_token_scanner *scanner);
t_token_type		peek_token(t_token_scanner *scanner);
t_token_type		peek_next_token(t_token_scanner *scanner);
bool				token_list_is_at_end(t_token_scanner *scanner);
bool				token_is_redirection(t_token_scanner *scanner);

/* ast_utils.c */
void				add_new_ast_node_cmd(t_parser *data, t_ast *cmd_node);
void				add_new_ast_node_pipe(t_parser *data, t_ast *cmd_node);

/* ast_content_utils.c */
t_parser_exit_code	add_redirection(t_parser *data, \
t_token_scanner *scanner, t_ast *cmd_node, t_redirect_type type);
t_parser_exit_code	add_assignment_word(t_parser *data, \
t_token_scanner *scanner, t_ast *cmd_node);
t_parser_exit_code	add_cmd_and_cmd_args(t_parser *data, \
t_token_scanner *scanner, t_ast *cmd_node);

/* parser_linked_list_utils.c */
void				add_redirect_back(t_redirect **io_redirect, \
t_redirect *new_redirect);
void				add_assignment_back(t_assignment **assignments, \
t_assignment *new_assignment);
void				free_redirect_list(t_redirect **io_redirect);
void				free_assignment_list(t_ast_content *content);

/* parser_free.c */
void				free_p(char	*p);
void				free_str_arr(char **arr);
void				free_ast(t_parser *data);
void				free_ast_content(t_ast_content *content);

/* parser_test.c */
void				parser_test(t_parser *data);

#endif