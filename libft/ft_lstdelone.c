/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarts <tmarts@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 15:07:55 by tmarts            #+#    #+#             */
/*   Updated: 2023/03/03 14:46:58 by tmarts           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
Takes as a parameter a node and frees the memory of
the node’s content using the function ’del’ given as a parameter 
and free the node. The memory of ’next’ is not.
*/

void	ft_lstdelone(t_list *lst, void (*del)(void*))
{
	if (lst == 0 || del == 0)
		return ;
	del(lst->content);
	free (lst);
	return ;
}
