/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_list_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunskim <eunskim@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 14:32:25 by eunskim           #+#    #+#             */
/*   Updated: 2023/05/29 14:34:09 by eunskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "lexer.h"
#include "../include/lexer.h"

void	free_token_list(t_lexer *data)
{
	t_token_list	*tmp;
	t_token_list	*tmp_to_free;

	tmp = data->head;
	tmp_to_free = tmp;
	while (tmp)
	{
		tmp = tmp->next;
		free(tmp_to_free);
		tmp_to_free = tmp;
	}
	data->head = NULL;
	data->tail = NULL;
}

void	update_lexer_data(t_lexer *data, t_token_list *token_node)
{
	if (data->head == NULL)
	{
		data->head = token_node;
		data->tail = token_node;
	}
	else
		data->tail = token_node;
}

void	add_token_node_back(t_token_list **head, t_token_list *new)
{
	t_token_list	*last;

	if (head == NULL || *head == NULL || new == NULL)
		return ;
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
