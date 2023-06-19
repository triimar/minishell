/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_linked_list_utils.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunskim <eunskim@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 21:10:27 by eunskim           #+#    #+#             */
/*   Updated: 2023/06/19 16:16:06 by eunskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	add_assignment_node_back(t_assignment **assignments, t_assignment *new_assignment)
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

void	add_redirect_node_back(t_redirect **io_redirect, t_redirect *new_redirect)
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
