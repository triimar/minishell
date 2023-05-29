/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarts <tmarts@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 18:27:37 by tmarts            #+#    #+#             */
/*   Updated: 2023/03/03 14:42:49 by tmarts           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
Counts the number of nodes in a list.
*/

int	ft_lstsize(t_list *lst)
{
	int		length;
	t_list	*current;

	current = lst;
	length = 0;
	while (current != 0)
	{
		current = current->next;
		length++;
	}
	return (length);
}
