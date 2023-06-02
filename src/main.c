/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunskim <eunskim@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 17:03:31 by tmarts            #+#    #+#             */
/*   Updated: 2023/06/02 16:32:43 by eunskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_strcmp(const char *s1, const char *s2)
{
	if (s1 == 0 || s2 == 0)
		return (0);
	while (*s1 != '\0' && *s2 != '\0' && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	if (*s1 || *s2)
		return (0);
	return (1);
}

int	main(int argc, char **argv)
{
	char	*p_input;

	if (argc != 1)
		return (0);
	(void)argv;
	while (1)
	{
		p_input = readline("eunskim-tmarts-m_sh % ");
		if (!p_input)
			break ;
		if (ft_strcmp(p_input, "exit"))
		{
			free(p_input);
			rl_clear_history();
			builtin_exit(0);
			// we should be taking the exit_code from the p_input, 
			// instead of this 'if' the exit should be parsed and run as any other cmmand
		}
		ft_putendl_fd(p_input, STDOUT_FILENO);
		if (p_input && *p_input)
			add_history(p_input);
		free(p_input);
	}
	rl_clear_history();
	return (0);
}
