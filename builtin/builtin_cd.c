/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunskim <eunskim@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 17:10:48 by eunskim           #+#    #+#             */
/*   Updated: 2023/07/19 17:07:27 by eunskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	cd_to_oldpwd(t_var_list *var_head, char *pwd)
{
	char	*oldpwd;

	oldpwd = ft_strdup(get_value_for_key(var_head, "OLDPWD"));
	if (oldpwd == NULL)
		return (free(pwd), printf("Malloc failed.\n"), EXIT_FAILURE);
	if (chdir(get_value_for_key(var_head, "OLDPWD")) == -1)
		return (free(pwd), free(oldpwd), \
		printf("minishell: cd: %s\n", strerror(errno)), EXIT_FAILURE);
	if (change_value_for_key(var_head, "OLDPWD", pwd))
		return (free(pwd), free(oldpwd), \
		printf("Malloc failed.\n"), EXIT_FAILURE);
	if (change_value_for_key(var_head, "PWD", oldpwd))
		return (free(pwd), free(oldpwd), \
		printf("Malloc failed.\n"), EXIT_FAILURE);
	return (free(pwd), free(oldpwd), EXIT_SUCCESS);
}

int	cd_to_home(t_var_list *var_head, char *pwd)
{
	if (chdir(get_value_for_key(var_head, "HOME")) == -1)
		return (free(pwd), \
		printf("minishell: cd: %s\n", strerror(errno)), EXIT_FAILURE);
	if (change_value_for_key(var_head, "OLDPWD", pwd))
		return (free(pwd), printf("Malloc failed.\n"), EXIT_FAILURE);
	if (change_value_for_key(var_head, "PWD", \
	get_value_for_key(var_head, "HOME")))
		return (free(pwd), printf("Malloc failed.\n"), EXIT_FAILURE);
	return (free(pwd), EXIT_SUCCESS);
}

int	builtin_cd(t_var_list *var_head, char **cmd)
{
	char	*pwd;

	pwd = getcwd(NULL, PATH_MAX);
	if (pwd == NULL)
		return (printf("minishell: cd: %s\n", strerror(errno)), EXIT_FAILURE);
	if (cmd[1] == NULL || (cmd[1][0] == '~' && cmd[1][1] == '\0'))
		return (cd_to_home(var_head, pwd));
	else if (cmd[1][0] == '-' && cmd[1][1] == '\0')
		return (cd_to_oldpwd(var_head, pwd));
	else if (cmd[1][0] == '\0')
		return (free(pwd), EXIT_SUCCESS);
	else
	{
		if (chdir(cmd[1]) == -1)
			return (free(pwd), printf("minishell: cd: %s\n", strerror(errno)), EXIT_FAILURE);
		if (change_value_for_key(var_head, "OLDPWD", pwd))
			return (free(pwd), printf("Malloc failed.\n"), EXIT_FAILURE);
		free(pwd);
		pwd = getcwd(NULL, PATH_MAX);
		if (pwd == NULL)
			return (printf("minishell: cd %s\n", strerror(errno)), EXIT_FAILURE);
		if (change_value_for_key(var_head, "PWD", pwd))
			return (free(pwd), printf("Malloc failed.\n"), EXIT_FAILURE);
	}
	return (free(pwd), EXIT_SUCCESS);
}
