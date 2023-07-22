/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_execution.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarts <tmarts@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 16:54:25 by tmarts            #+#    #+#             */
/*   Updated: 2023/07/22 19:16:53 by tmarts           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	is_builtin(char *cmd)
{
	if (ft_strncmp(cmd, "echo", 5) == 0)
		return (1);
	if (ft_strncmp(cmd, "cd", 3) == 0)
		return (1);
	if (ft_strncmp(cmd, "env", 4) == 0)
		return (1);
	if (ft_strncmp(cmd, "pwd", 4) == 0)
		return (1);
	if (ft_strncmp(cmd, "export", 7) == 0)
		return (1);
	if (ft_strncmp(cmd, "unset", 6) == 0)
		return (1);
	if (ft_strncmp(cmd, "exit", 5) == 0)
		return (1);
	return (0);
}

int	run_builtin(t_var_list *var_list, char **cmd)
{
	if (ft_strncmp(cmd[0], "echo", 5) == 0)
		return (builtin_echo(cmd));
	if (ft_strncmp(cmd[0], "cd", 3) == 0)
		return (builtin_cd(var_list, cmd));
	if (ft_strncmp(cmd[0], "env", 4) == 0)
		return (builtin_env(var_list));
	if (ft_strncmp(cmd[0], "pwd", 4) == 0)
		return (builtin_pwd());
	if (ft_strncmp(cmd[0], "export", 7) == 0)
		return (0);
	if (ft_strncmp(cmd[0], "unset", 6) == 0)
		return (0);
	return (0);
}
