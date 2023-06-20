/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_linked_list_utils.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunskim <eunskim@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 21:10:27 by eunskim           #+#    #+#             */
/*   Updated: 2023/06/20 19:53:33 by eunskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	free_assignment_list(t_ast_content *content)
{
	t_assignment	*tmp;
	t_assignment	*tmp_to_free;

	if (content->assignments == NULL)
		return ;
	tmp = content->assignments;
	tmp_to_free = tmp;
	while (tmp)
	{
		free_p(tmp->word);
		tmp = tmp->next;
		free(tmp_to_free);
		tmp_to_free = tmp;
	}
	content->assignments = NULL;
}

void	free_redirect_list(t_redirect **io_redirect)
{
	t_redirect	*tmp;
	t_redirect	*tmp_to_free;

	if (io_redirect == NULL || *io_redirect == NULL)
		return ;
	tmp = *io_redirect;
	tmp_to_free = tmp;
	while (tmp)
	{
		free_p(tmp->word);
		tmp = tmp->next;
		free(tmp_to_free);
		tmp_to_free = tmp;
	}
	*io_redirect = NULL;
}

void	add_assignment_back(t_assignment **assignments, \
t_assignment *new_assignment)
{
	t_assignment	*last;

	if (assignments == NULL || new_assignment == NULL)
		return ;
	if (*assignments == NULL)
	{
		*assignments = new_assignment;
		return ;
	}	
	last = *assignments;
	while (last->next != NULL)
		last = last->next;
	last->next = new_assignment;
}

void	add_redirect_back(t_redirect **io_redirect, \
t_redirect *new_redirect)
{
	t_redirect	*last;

	if (io_redirect == NULL || new_redirect == NULL)
		return ;
	if (*io_redirect == NULL)
	{
		*io_redirect = new_redirect;
		return ;
	}	
	last = *io_redirect;
	while (last->next != NULL)
		last = last->next;
	last->next = new_redirect;
}
