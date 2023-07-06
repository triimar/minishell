/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_test.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunskim <eunskim@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 17:36:35 by eunskim           #+#    #+#             */
/*   Updated: 2023/07/06 20:23:21 by eunskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char	*quote_removal(char *str, int *i, bool *malloc_failed)
{
	int		cnt;
	int		len;
	char	quote;
	char	*result;

	cnt = 0;
	len = (int) strlen(str);
	quote = *(str + *i);
	while (*(str + *i + cnt + 1) != quote)
		cnt++;
	result = (char *) calloc(1, len - 2 + 1);
	if (result == NULL)
	{
		*malloc_failed = true;
		return (NULL);
	}
	memmove(result, str, *i);
	memmove(result + *i, str + *i + 1, cnt);
	memmove(result + *i + cnt, str + *i + cnt + 2, len - *i - cnt - 2);
	*i = *i + cnt - 1;
	free(str);
	return (result);
}

char	*quote_removal_here_end(char *here_end, bool *malloc_failed)
{
	int	i;

	i = 0;
	while (*(here_end + i) != '\0')
	{
		if (*malloc_failed == true)
			break ;
		if (*(here_end + i) == '\"' || *(here_end + i) == '\'')
			here_end = quote_removal(here_end, &i, malloc_failed);
		i++;
	}
	return (here_end);
}

int	main(int argc, char **argv)
{
	char	*here_end;
	bool	malloc_failed;

	system("leaks a.out");
	if (argc != 2)
		return (EXIT_FAILURE);
	here_end = strdup((const char *) argv[1]);
	malloc_failed = false;
	printf("Before removal: %s\n", here_end);
	here_end = quote_removal_here_end(here_end, &malloc_failed);
	if (malloc_failed == true)
	{
		printf("Malloc failed.\n");
		return (1);
	}
	printf("After removal: %s\n", here_end);
	free(here_end);
	return (0);
}

// int	main(int argc, char **argv, char **envp)
// {
// 	char	*to_expand;

// 	if (argc != 2)
// 		return (EXIT_FAILURE);
// 	to_expand = ft_strdup((const char *) argv[1]);
// 	printf("Before expansion: %s\n", to_expand);
// 	expander(to_expand, envp);
// 	printf("After expansion: %s\n", to_expand);
// 	free(to_expand);
// }
