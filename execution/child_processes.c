/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_processes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarts <tmarts@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 19:32:12 by tmarts            #+#    #+#             */
/*   Updated: 2023/07/22 00:29:52 by tmarts           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	child_execve_process(t_minishell *ms_data, char **cmd)
{
	t_exec	exec_data;

	exec_data.envp = NULL;
	exec_data.path = NULL;
	if (get_envp(&exec_data, ms_data->var_head) != 0)
		exit(EXIT_FAILURE);
	if (get_right_path(&exec_data, cmd[0]) != 0)
		child_error(ms_data, &exec_data, 1, cmd[0]);
	if (!exec_data.path)
		child_error(ms_data, &exec_data, 127, cmd[0]);
	if (access(exec_data.path, X_OK) != 0)
		child_error(ms_data, &exec_data, 126, cmd[0]);
	execve(exec_data.path, cmd, exec_data.envp);
	child_error(ms_data, &exec_data, -1, cmd[0]);
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

