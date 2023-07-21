/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_errors.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarts <tmarts@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 20:29:46 by tmarts            #+#    #+#             */
/*   Updated: 2023/07/21 22:42:45 by tmarts           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	child_error(t_minishell *ms_data, t_exec *exec_data, \
														int exitcode, char *cmd)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	if (exitcode == 1)
		ft_putendl_fd(" malloc error", STDERR_FILENO);
	if (exitcode == 127)
	{
		ft_putstr_fd(cmd, STDERR_FILENO);
		ft_putendl_fd(": command not found", STDERR_FILENO);
	}
	if (exitcode == 126)
	{
		ft_putstr_fd(cmd, STDERR_FILENO);
		ft_putendl_fd(": command not executable", STDERR_FILENO);
	}
	if (exitcode == -1)
		ft_putendl_fd("minishell: execve error: ", STDERR_FILENO);
	if (exec_data->path)
		free(exec_data->path);
	if (exec_data->envp)
		ft_free_pp(exec_data->envp);
	free_on_exit(ms_data);
	exit(exitcode);
}