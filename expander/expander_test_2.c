/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_test_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunskim <eunskim@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 20:40:49 by eunskim           #+#    #+#             */
/*   Updated: 2023/07/11 21:03:01 by eunskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int	main(int argc, char **argv, char **envp)
{
	char	*to_expand;
	bool	malloc_failed;

	malloc_failed = false;
	if (argc != 2)
		return (EXIT_FAILURE);
	to_expand = ft_strdup((const char *) argv[1]);
	printf("Before expansion: %s\n", to_expand);
	to_expand = substring_expansion(to_expand, envp);
	printf("After expansion: %s\n", to_expand);
	free(to_expand);
}
