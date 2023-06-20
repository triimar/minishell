/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   for_test.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunskim <eunskim@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 16:22:15 by eunskim           #+#    #+#             */
/*   Updated: 2023/06/20 18:50:31 by eunskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	print_token(t_token_list *token_head)
{
	t_token_list	*tmp;

	tmp = token_head;
	printf("\n------------ TOKEN LIST -----------\n\n");
	while (tmp)
	{
		if (tmp->token.type == TOKEN_EOF)
			printf("TOKEN_EOF\n");
		else if (tmp->token.type == TOKEN_WORD)
			printf("TOKEN_WORD\n");
		else if (tmp->token.type == TOKEN_ASSIGNMENT_WORD)
			printf("TOKEN_ASSIGHMENT_WORD\n");
		else if (tmp->token.type == TOKEN_GREAT)
			printf("TOKEN_GREAT\n");
		else if (tmp->token.type == TOKEN_DGREAT)
			printf("TOKEN_DGREAT\n");
		else if (tmp->token.type == TOKEN_LESS)
			printf("TOKEN_LESS\n");
		else if (tmp->token.type == TOKEN_DLESS)
			printf("TOKEN_DLESS\n");
		else if (tmp->token.type == TOKEN_PIPE)
			printf("TOKEN_PIPE\n");
		else if (tmp->token.type == TOKEN_ERROR)
			printf("TOKEN_ERROR\n");
		write(1, "  |  [", 6);
		write(1, tmp->token.start, tmp->token.length);
		write(1, "]  |  \n", 7);
		tmp = tmp->next;
	}
}

void	lexer_test(t_lexer *data)
{
	print_token(data->head);
	// free_token_list(data);
}

// int	main(int argc, char **argv)
// {
// 	if (argc != 2)
// 		return (INVALID_ARGUMENT);
// 	return (lexer(argv[1]));
// }
