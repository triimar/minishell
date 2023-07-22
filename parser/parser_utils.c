/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunskim <eunskim@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 18:40:52 by eunskim           #+#    #+#             */
/*   Updated: 2023/07/22 20:34:20 by eunskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	syntax_error_printer(t_token_scanner *scanner)
{
	if (token_is_redirection(scanner) == true)
		advance_token_list(scanner);
	ft_putstr_fd("minishell: syntax error near unexpected token `", \
	STDERR_FILENO);
	if (peek_token(scanner) == TOKEN_EOF)
		ft_putstr_fd("EOF", STDERR_FILENO);
	else
		write(STDERR_FILENO, scanner->token_current->token.start, \
		scanner->token_current->token.length);
	ft_putstr_fd("'\n", STDERR_FILENO);
	return ;
}

char	**extend_string_array(char **param, int word_cnt)
{
	int		i;
	char	**str_arr;

	i = 0;
	str_arr = (char **) ft_calloc(word_cnt + 2, sizeof(char *));
	while (i < word_cnt)
	{
		*(str_arr + i) = *(param + i);
		i++;
	}
	if (param != NULL)
		free(param);
	return (str_arr);
}

char	*produce_dup_string(const char *start, int length)
{
	int		i;
	char	*str;

	i = 0;
	if (length == 0)
		return (NULL);
	str = (char *) malloc(length + 1);
	if (str == NULL)
		return (NULL);
	while (i < length)
	{
		str[i] = start[i];
		i++;
	}
	str[length] = '\0';
	return (str);
}

void	init_parser_data(t_parser *data, t_token_scanner *scanner)
{
	data->ast_root = NULL;
	data->ast_current = data->ast_root;
	data->malloc_failed = false;
	data->scanner = scanner;
}

void	init_token_scanner(t_token_scanner *scanner, t_token_list *head)
{
	scanner->token_head = head;
	scanner->token_current = head;
}
