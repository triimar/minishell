/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunskim <eunskim@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 17:04:22 by eunskim           #+#    #+#             */
/*   Updated: 2023/07/14 21:49:38 by eunskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <limits.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int	builtin_pwd(void)
{
	char	*pwd;
	pwd = NULL;
	
	pwd = getcwd(pwd, PATH_MAX);
	if (pwd == NULL)
	{
		printf("Print error message here: %s\n", strerror(errno));
		return (EXIT_FAILURE);
	}
	printf("%s\n", pwd);
	free(pwd);
	return (EXIT_SUCCESS);
}

int main(void)
{
	return (builtin_pwd());
}
