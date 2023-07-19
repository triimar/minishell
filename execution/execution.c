/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarts <tmarts@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 16:11:11 by tmarts            #+#    #+#             */
/*   Updated: 2023/07/19 16:05:49 by tmarts           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include <sys/stat.h>

static t_exec_exit_code	execve_single(t_var_list *var_list, \
										char **cmd)
{
	int				pid;

	pid = fork();
	if (pid == -1)
		return (FORK_ERROR);
	if (pid == 0)
		child_process(var_list, cmd);
	ft_waiting(&pid, 1);
	return (EXEC_SUCCESS);
}

static t_exec_exit_code	exec_single_cmd(t_var_list *var_list, \
										t_ast_content *cmd_node)
{
	if (ft_strncmp(cmd_node->cmd[0], "echo", 5) == 0)
		return (0);
	else if (ft_strncmp(cmd_node->cmd[0], "cd", 3) == 0)
		return (0);
	else if (ft_strncmp(cmd_node->cmd[0], "pwd", 4) == 0)
		return (0);
	else if (ft_strncmp(cmd_node->cmd[0], "cd", 3) == 0)
		return (0);
	else if (ft_strncmp(cmd_node->cmd[0], "export", 7) == 0)
		return (0);
	else if (ft_strncmp(cmd_node->cmd[0], "unset", 6) == 0)
		return (0);
	else if (ft_strncmp(cmd_node->cmd[0], "env", 4) == 0)
		return (0);
	else if (ft_strncmp(cmd_node->cmd[0], "exit", 5) == 0)
		return (builtin_exit(1), 0); //rewrite so that it takes char * as input
	else
		return (execve_single(var_list, cmd_node->cmd));

}

t_exec_exit_code	add_to_var_list(t_var_list *var_list, t_assignment *assign)
{
	t_var_list		*oi;
	t_assignment	*ai;

	oi = var_list;
	ai = assign;
	return (EXEC_SUCCESS);
}

static t_exec_exit_code	single_node(t_minishell *ms_data, \
									t_ast_content *cmd_node)
{
	int	stdin_save;
	int	stdout_save;

	if (redirect_main(&stdin_save, cmd_node->stdin_redirect, \
			&stdout_save, cmd_node->stdout_redirect) != 0)
		return (EXEC_FAIL);
	if (cmd_node->cmd == NULL)
	{
		if (add_to_var_list(ms_data->var_head, \
		cmd_node->assignments) != EXEC_SUCCESS)
			return (restore_redirect(stdin_save, stdout_save), EXEC_FAIL);
	}
	else
	{
		if (exec_single_cmd(ms_data->var_head, cmd_node) != EXEC_SUCCESS)
			return (restore_redirect(stdin_save, stdout_save), EXEC_FAIL);
	}
	restore_redirect(stdin_save, stdout_save);
	return (EXEC_SUCCESS);
}

t_exec_exit_code	executor(t_minishell *ms_data, t_parser *parser_data)
{	
	if (parser_data->ast_root->content != NULL)
	{
		if (single_node(ms_data, parser_data->ast_root->content) != \
															EXEC_SUCCESS)
			return (EXEC_FAIL);
	}
	else
	{
		if (piper(ms_data->var_head, parser_data) != EXEC_SUCCESS)
			return (EXEC_FAIL);
		return (EXEC_SUCCESS);
	}
	return (EXEC_SUCCESS);
}
