/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunskim <eunskim@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 13:47:39 by eunskim           #+#    #+#             */
/*   Updated: 2023/07/16 17:11:44 by eunskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	check_option_n(char **arg)
{
	int	i;
	int	j;

	i = 0;
	j = 1;
	while (*(arg + i) != NULL)
	{
		if (arg[i][0] != '-')
			return (i);
		//
	}
}

int	builtin_echo(char **cmd)
{
	int		i;
	int		cnt;
	int		option_n;
	char	*tmp;
	char	*tmp_dup;

	i = 0;
	cnt = 0;
	option_n = false;
	while (*(cmd + cnt) != NULL)
		cnt++;
	if (cnt == 1)
		return (ft_putstr_fd("\n", STDOUT_FILENO), EXIT_SUCCESS);
	option_n = check_option_n(cmd + 1);
	while (cnt - i > 2 + option_n)
	{
		if (i == 0)
		{
			tmp = ft_strdup(cmd[cnt - 1]);
			if (tmp == NULL)
				return (ft_putendl_fd("Malloc failed.", STDOUT_FILENO));
		}
		else
		{
			tmp = ft_strjoin_sym(cmd[cnt - 1 - i], tmp_dup, ' ');
			if (tmp == NULL)
				return (ft_putendl_fd("Malloc failed.", STDOUT_FILENO));
			free(tmp_dup);
		}
		tmp_dup = ft_strdup(tmp);
		if (tmp_dup == NULL)
			return (free(tmp), ft_putendl_fd("Malloc failed.", STDOUT_FILENO));
		free(tmp);
		i++;
	}
	printf("%s", tmp_dup);
	if (option_n == 0)
		printf("\n");
	free_p(tmp_dup);
	return (EXIT_SUCCESS);
}