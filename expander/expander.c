/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunskim <eunskim@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 18:18:08 by eunskim           #+#    #+#             */
/*   Updated: 2023/07/05 17:46:47 by eunskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

int	double_quote_expansion(char *str)
{
	int	i;

	i = 1;
	while (str[i] != '\"')
	{
		if (str[i] == '$')
		{
			get_variable_name(str + i);
		}
		i++;
	}
}

int remove_quotes(char *str)
{
	int	i;

	i = 0;
	while (true)
	{
		if (str[i] == '\"' || str)
	}
}



int	expander(t_parser *parser_data, t_var_list *var_head)
{
	int	i;

	i = 0;
	while (true)
	{
		while (str[i])
		{
			if (str[i] == '\"')
				double_quote_expansion(str + i);
			
			i++;
		}
	}
}
