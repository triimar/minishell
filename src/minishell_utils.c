/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarts <tmarts@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 23:29:15 by tmarts            #+#    #+#             */
/*   Updated: 2023/07/08 20:45:53 by tmarts           ###   ########.fr       */
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

/* ft_strjoin, but adds specified character between the two strings */
char	*ft_strjoin_sym(const char *s1, const char *s2, char c)
{
	char	*test_path;
	int		s1_len;
	int		s2_len;

	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	test_path = malloc(s1_len + s2_len + 2);
	if (!test_path)
		return (NULL);
	while (s1 && *s1 != 0)
		*test_path++ = *s1++;
	*test_path = c;
	test_path++;
	while (*s2 != '\0')
		*test_path++ = *s2++;
	*test_path = '\0';
	return (test_path - s1_len - s2_len - 1);
}

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
