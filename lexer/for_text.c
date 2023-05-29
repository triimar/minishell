/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   for_text.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunskim <eunskim@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 16:22:15 by eunskim           #+#    #+#             */
/*   Updated: 2023/05/29 16:33:15 by eunskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "lexer.h"
#include "../include/lexer.h"

void	print_token_type(t_lexer *data)
{
	t_token_list	*tmp;

	tmp = data->head;
	if (tmp)
	{
		if (tmp->token->type == TOKEN_EOF)
			printf("TOKEN_EOF\n");
		else if (tmp->token->type == TOKEN_WORD)
			printf("TOKEN_WORD\n");
		else if (tmp->token->type == TOKEN_GREAT)
			printf("TOKEN_GREAT\n");
		else if (tmp->token->type == TOKEN_DGREAT)
			printf("TOKEN_DGREAT\n");
		else if (tmp->token->type == TOKEN_LESS)
			printf("TOKEN_LESS\n");
		else if (tmp->token->type == TOKEN_DLESS)
			printf("TOKEN_DLESS\n");
		else if (tmp->token->type == TOKEN_PIPE)
			printf("TOKEN_PIPE\n");
		else if (tmp->token->type == TOKEN_ERROR)
			printf("TOKEN_ERROR\n");
		tmp = tmp->next;
	}
}

void	lexer_test(t_lexer *data)
{
	print_token_type(data);
	free_token_list(data);
}

int	main(int argc, char **argv)
{
	int	lexer_exit_code;

	if (argc != 2)
		printf("invalid input");
	else
		lexer_exit_code = lexer(argv[1]);
	return (lexer_exit_code);
}