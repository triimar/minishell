/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_test.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunskim <eunskim@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 17:36:35 by eunskim           #+#    #+#             */
/*   Updated: 2023/07/05 17:44:29 by eunskim          ###   ########.fr       */
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

int	expander(char *str, char **envp)
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

int	main(int argc, char **argv, char **envp)
{
	char	*to_expand;

	if (argc != 2)
		return (EXIT_FAILURE);
	to_expand = ft_strdup((const char *) argv[1]);
	printf("Before expansion: %s\n", to_expand);
	expander(to_expand, envp);
	printf("After expansion: %s\n", to_expand);
	free(to_expand);
}
