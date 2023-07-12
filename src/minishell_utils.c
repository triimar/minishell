/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunskim <eunskim@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 23:29:15 by tmarts            #+#    #+#             */
/*   Updated: 2023/07/12 18:47:38 by eunskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_lstadd_back_ms(t_var_list **var_list, t_var_list *new)
{
	t_var_list	*last;

	if (*var_list == 0)
	{
		*var_list = new;
		return ;
	}		
	last = *var_list;
	while (last->next != NULL)
		last = last->next;
	last->next = new;
	return ;
}

int	ft_lstsize_ms(t_var_list *lst)
{
	int			length;
	t_var_list	*current;

	current = lst;
	length = 0;
	while (current != NULL)
	{
		current = current->next;
		length++;
	}
	return (length);
}

t_var_list	*ft_lstlast_ms(t_var_list *lst)
{
	t_var_list	*current;

	current = lst;
	while (current != NULL)
	{
		if (current->next == NULL)
			return (current);
		current = current->next;
	}	
	return (0);
}
