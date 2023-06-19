/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_node_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunskim <eunskim@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 17:18:10 by eunskim           #+#    #+#             */
/*   Updated: 2023/06/19 15:44:03 by eunskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_parser_exit_code	add_cmd_and_cmd_args(t_parser *data, t_token_scanner *scanner, t_ast *cmd_node)
{
	int	word_cnt;

	word_cnt = 0;
	while (cmd_node->content->cmd + word_cnt != NULL)
		word_cnt++;
	cmd_node->content->cmd = extend_string_array(cmd_node->content->cmd, word_cnt);
	if (cmd_node->content->cmd == NULL)
	{
		data->malloc_failed = true;
		return (PARSER_FAILURE);
	}
	cmd_node->content->cmd[word_cnt] = produce_dup_string(scanner->token_current->token.start, scanner->token_current->token.length);
	if (cmd_node->content->cmd[word_cnt] == NULL)
	{
		data->malloc_failed = true;
		return (PARSER_FAILURE);
	}
	advance_token_list(scanner);
	return (PARSER_SUCCESS);
}

t_parser_exit_code	add_assignment_word(t_parser *data, t_token_scanner *scanner, t_ast *cmd_node)
{
	t_assignment	*new_assignment;

	new_assignment = (t_assignment *) ft_calloc(1, sizeof(t_assignment));
	if (new_assignment == NULL)
	{
		data->malloc_failed = true;
		return (PARSER_FAILURE);
	}
	new_assignment->word = produce_dup_string(scanner->token_current->token.start, scanner->token_current->token.length);
	if (new_assignment->word == NULL)
	{
		free(new_assignment);
		data->malloc_failed = true;
		return (PARSER_FAILURE);
	}
	add_assignment_node_back(&(cmd_node->content->assignments), new_assignment);
	advance_token_list(scanner);
	return (PARSER_SUCCESS);
}

t_parser_exit_code	add_redirection(t_parser *data, t_token_scanner *scanner, t_ast *cmd_node, t_redirect_type type)
{
	t_redirect			*new_redirect;

	new_redirect = (t_redirect *) ft_calloc(1, sizeof(t_redirect));
	if (new_redirect == NULL)
	{
		data->malloc_failed = true;
		return (PARSER_FAILURE);
	}
	new_redirect->type = type;
	advance_token_list(scanner);
	new_redirect->word = produce_dup_string(scanner->token_current->token.start, scanner->token_current->token.length);
	if (new_redirect->word == NULL)
	{
		free(new_redirect);
		data->malloc_failed = true;
		return (PARSER_FAILURE);
	}
	if (type == REDIRECT_STDIN || type == REDIRECT_HERE_DOC)
		add_redirect_node_back(&(cmd_node->content->stdin_redirect), new_redirect);
	if (type == REDIRECT_STDOUT || type == REDIRECT_STDOUT_APPEND)
		add_redirect_node_back(&(cmd_node->content->stdout_redirect), new_redirect);
	advance_token_list(scanner);
	return (PARSER_SUCCESS);
}
