/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarts <tmarts@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 16:11:11 by tmarts            #+#    #+#             */
/*   Updated: 2023/07/22 18:19:06 by tmarts           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include <sys/stat.h>

static t_exec_exit_code	one_fork(t_minishell *ms_data, char **cmd)
{
	int				pid;

	pid = fork();
	if (pid == -1)
		return (FORK_ERROR);
	if (pid == 0)
		child_execve_process(ms_data, cmd);
	ft_waiting(&pid, 1, &ms_data->exit_code);
	if (ms_data->exit_code != 0)
		return (EXEC_FAIL);
	return (EXEC_SUCCESS);
}

static t_exec_exit_code	single_cmd(t_minishell *ms_data, \
										t_ast_content *cmd_node, int *fildes)
{
	int	save_stdin_out[2];

	save_stdin_out[0] = dup(STDIN_FILENO);
	save_stdin_out[1] = dup(STDOUT_FILENO);
	redirect(fildes[0], fildes[1]);
	if (is_builtin(cmd_node->cmd[0]))
	{
		if (ft_strncmp(cmd_node->cmd[0], "exit", 5) == 0)
		{
			restore_redirect(save_stdin_out[0], save_stdin_out[1]);
			ms_data->exit_code = builtin_exit(ms_data, cmd_node->cmd);
		}
		else
			ms_data->exit_code = run_builtin(ms_data->var_head, cmd_node->cmd);
	}
	else
	{
		one_fork(ms_data, cmd_node->cmd);
	}
	restore_redirect(save_stdin_out[0], save_stdin_out[1]);
	if (ms_data->exit_code != 0)
		return (EXEC_FAIL);
	return (EXEC_SUCCESS);
}

static t_exec_exit_code	single_node(t_minishell *ms_data, \
														t_ast_content *cmd_node)
{
	int	fd_in_out[2];

	fd_in_out[0] = STDIN_FILENO;
	fd_in_out[1] = STDOUT_FILENO;
	if (open_files(fd_in_out, cmd_node->stdin_redirect, \
												cmd_node->stdout_redirect) != 0)
		return (EXEC_FAIL);
	if (cmd_node->cmd == NULL && cmd_node->assignments != NULL)
	{
		if (add_assignments(ms_data->var_head, \
									cmd_node->assignments, 0) != EXEC_SUCCESS)
		{
			close(fd_in_out[0]);
			close (fd_in_out[1]);
			return (EXEC_FAIL);
		}
	}
	else if (single_cmd(ms_data, cmd_node, fd_in_out) \
															!= EXEC_SUCCESS)
		return (EXEC_FAIL);
	return (EXEC_SUCCESS);
}

t_exec_exit_code	executor(t_minishell *ms_data, t_parser *parser_data)
{	
	if (parser_data->ast_root == NULL)
		return (EXEC_SUCCESS);
	if (parser_data->ast_root->content != NULL)
	{
		if (single_node(ms_data, parser_data->ast_root->content) != \
															EXEC_SUCCESS)
			return (EXEC_FAIL);
	}
	else
	{
		if (piper(ms_data, parser_data) != EXEC_SUCCESS)
			return (EXEC_FAIL);
	}
	return (EXEC_SUCCESS);
}
