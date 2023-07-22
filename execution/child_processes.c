/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_processes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarts <tmarts@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 19:32:12 by tmarts            #+#    #+#             */
/*   Updated: 2023/07/22 17:29:35 by tmarts           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include <sys/stat.h>

static void	free_execve(t_minishell *ms_data, t_exec *exec_data)
{
	if (exec_data->path)
		free(exec_data->path);
	if (exec_data->envp)
		ft_free_pp(exec_data->envp);
	free_on_exit(ms_data);
}

void	child_execve_process(t_minishell *ms_data, char **cmd)
{
	struct stat	path_stat;
	t_exec		exec_data;

	exec_data.envp = NULL;
	exec_data.path = NULL;
	if (get_envp(&exec_data, ms_data->var_head) != 0)
		exit(EXIT_FAILURE);
	if (get_right_path(&exec_data, cmd[0]) != 0)
	{
		error_printer(cmd[0], NULL, "malloc fail");
		free_execve(ms_data, &exec_data);
		exit (1);
	}
	if (!exec_data.path)
	{
		error_printer(cmd[0], NULL, "command not found");
		free_execve(ms_data, &exec_data);
		exit (127);
	}
	if (stat(exec_data.path, &path_stat) == -1)
	{
		internal_error_printer("STAT(1)");
		free_execve(ms_data, &exec_data);
		exit (127);
	}
	if (S_ISDIR(path_stat.st_mode))
	{
		error_printer(cmd[0], NULL, "is a directory");
		free_execve(ms_data, &exec_data);
		exit (126);
	}
	if (access(exec_data.path, X_OK) != 0)
	{
		error_printer(cmd[0], NULL, "command not executable");
		free_execve(ms_data, &exec_data);
		exit (126);
	}
	execve(exec_data.path, cmd, exec_data.envp);
	error_printer(cmd[0], NULL, strerror(errno));
	free_execve(ms_data, &exec_data);
	exit (-1);
}

void	child_with_pipes(t_minishell *ms_data, t_piper *piper)
{
	redirect_in_child(piper);
	if (piper->cmd_node->cmd == NULL)
	{
		free_on_exit(ms_data);
		exit(EXIT_FAILURE);
	}
	if (is_builtin(piper->cmd_node->cmd[0]))
	{
		if (ft_strncmp(piper->cmd_node->cmd[0], "exit", 5) == 0)
			ms_data->exit_code = builtin_exit(ms_data, piper->cmd_node->cmd);
		else
			ms_data->exit_code = \
						run_builtin(ms_data->var_head, piper->cmd_node->cmd);
	}	
	else
		child_execve_process(ms_data, piper->cmd_node->cmd);
	free(piper->pids);
	free_on_exit(ms_data);
	exit(ms_data->exit_code);
}

