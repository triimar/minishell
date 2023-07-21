/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunskim <eunskim@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 17:04:22 by eunskim           #+#    #+#             */
/*   Updated: 2023/07/21 17:59:37 by eunskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	builtin_pwd(void)
{
	char	*pwd;

	pwd = NULL;
	pwd = getcwd(pwd, PATH_MAX);
	if (pwd == NULL)
	{
		error_printer("pwd", NULL, strerror(errno));
		return (EXIT_FAILURE);
	}
	printf("%s\n", pwd);
	free(pwd);
	return (EXIT_SUCCESS);
}
