/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_list_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunskim <eunskim@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 14:32:25 by eunskim           #+#    #+#             */
/*   Updated: 2023/06/01 15:56:43 by eunskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

// void	iter_token_list(t_lexer *data, void (*f)(void *))
// {
// 	t_token_list	*tmp;

// 	tmp = data->head;
// 	while (tmp)
// 	{
// 		f((void *) tmp->token);
// 		tmp = tmp->next;
// 	}
// }

void	free_token_list(t_lexer *data)
{
	t_token_list	*tmp;
	t_token_list	*tmp_to_free;

	if (data->head == NULL)
		return ;
	tmp = data->head;
	tmp_to_free = tmp;
	while (tmp)
	{
		tmp = tmp->next;
		free(tmp_to_free);
		tmp_to_free = tmp;
	}
	data->head = NULL;
}

void	add_token_node_back(t_token_list **head, t_token_list *new)
{
	t_token_list	*last;

	if (head == NULL || new == NULL)
		return ;
	if (*head == NULL)
	{
		*head = new;
		return ;
	}
	last = *head;
	while (last->next != NULL)
		last = last->next;
	last->next = new;
}

t_token_list	*make_token_node(t_token token)
{
	t_token_list	*token_node;

	token_node = NULL;
	token_node = (t_token_list *) malloc(sizeof(t_token_list));
	if (token_node == NULL)
		return (NULL);
	token_node->token = token;
	token_node->next = NULL;
	return (token_node);
}
