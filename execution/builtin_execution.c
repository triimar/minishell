/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_execution.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarts <tmarts@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 16:54:25 by tmarts            #+#    #+#             */
/*   Updated: 2023/07/26 16:56:24 by tmarts           ###   ########.fr       */
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

int	run_builtin(t_minishell *ms_data, char **cmd)
{
	if (ft_strncmp(cmd[0], "echo", 5) == 0)
		return (builtin_echo(cmd));
	if (ft_strncmp(cmd[0], "cd", 3) == 0)
		return (builtin_cd(ms_data->var_head, cmd));
	if (ft_strncmp(cmd[0], "env", 4) == 0)
		return (builtin_env(ms_data->var_head, cmd));
	if (ft_strncmp(cmd[0], "pwd", 4) == 0)
		return (builtin_pwd());
	if (ft_strncmp(cmd[0], "export", 7) == 0)
		return (builtin_export(ms_data->var_head, cmd));
	if (ft_strncmp(cmd[0], "unset", 6) == 0)
		return (builtin_unset(ms_data, cmd));
	return (0);
}
