/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarts <tmarts@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 17:56:07 by tmarts            #+#    #+#             */
/*   Updated: 2023/03/03 14:51:05 by tmarts           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
Iterates the list ’lst’ and applies the function ’f’ on the content of each 
node. Creates a new list resulting of the successive applications of
the function ’f’. The ’del’ function is used to delete the content of a node 
if needed.
*/

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*current;
	t_list	*new_node;
	t_list	*new_list;
	void	*content;

	if (!f || !del)
		return (NULL);
	current = lst;
	if (lst == 0)
		return (NULL);
	new_list = NULL;
	while (current != 0)
	{
		content = f(current->content);
		new_node = ft_lstnew(content);
		if (new_node == 0)
		{
			ft_lstclear(&new_list, del);
			free(content);
			return (NULL);
		}	
		ft_lstadd_back(&new_list, new_node);
		current = current->next;
	}
	return (new_list);
}
