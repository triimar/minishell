/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunskim <eunskim@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 18:18:08 by eunskim           #+#    #+#             */
/*   Updated: 2023/07/06 14:56:46 by eunskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

void	quote_removal_here_end(char *here_end, t_var_list *var_head, bool *malloc_failed)
{
	int		i;

	i = 0;
	while (*(here_end + i) != '\0')
	{
		if (*(here_end + i) == '\"' || *(here_end + i) == '\'')
			quote_removal(here_end, &i, malloc_failed);
		i++;
	}
}

void	expander(char *to_expand, t_var_list *var_head, bool *malloc_failed)
{
	int	i;

	i = 0;
	while (*(to_expand + i) != '\0')
	{
		if (*(to_expand + i) == '\"')
			double_quote_expansion(to_expand, &i, var_head, malloc_failed);
		if (*(to_expand + i) == '\'')
			quote_removal(to_expand, &i, malloc_failed);
		i++;
	}
}
