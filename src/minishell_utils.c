/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarts <tmarts@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 23:29:15 by tmarts            #+#    #+#             */
/*   Updated: 2023/07/04 23:30:50 by tmarts           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* char	*ft_strndup_pt(const char *start, char *delimiter)
Returns a pointer to a null-terminated byte string, which contains 
copies of at most size bytes from the string pointed to by str */
char	*ft_strdup_pt(const char *start, char *delimiter)
{
	char	*dst;
	int		len;

	len = 0;
	if (!start || !delimiter || delimiter < start)
		return (NULL);
	while (start + len != delimiter && *(start + len) != '\0')
		len++;
	dst = malloc((len + 1) * sizeof(char));
	if (!dst)
		return (NULL);
	ft_strlcpy(dst, start, len + 1);
	return (dst);
}

void	ft_lstadd_back_mini(t_var_list **var_list, t_var_list *new)
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