/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_processes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarts <tmarts@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 19:32:12 by tmarts            #+#    #+#             */
/*   Updated: 2023/07/21 22:09:25 by tmarts           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

static void	pipes_dup_close(int pipe_read[], int pipe_write[], t_piper *piper)
{
	close(pipe_read[1]);
	close(pipe_write[0]);
	if (piper->cmd_node->stdin_redirect != NULL)
	{
		close(pipe_read[0]);
		dup2(piper->infile, STDIN_FILENO);
	}
	else
		dup2(pipe_read[0], STDIN_FILENO);
	if (piper->cmd_node->stdout_redirect != NULL)
	{
		close(pipe_write[1]);
		dup2(piper->outfile, STDOUT_FILENO);
	}
	else
		dup2(pipe_write[1], STDOUT_FILENO);
}

static void	child_first(t_piper *piper)
{
	close(piper->pipe1[0]);
	if (piper->cmd_node->stdout_redirect != NULL)
	{
		close(piper->pipe1[1]);
		redirect(piper->infile, piper->outfile);
	}
	redirect(piper->infile, piper->pipe1[1]);
}

static void	child_last(t_piper *piper, int child_nr)
{
	if (child_nr % 2 == 0)
	{
		close(piper->pipe1[1]);
		if (piper->cmd_node->stdin_redirect != NULL)
		{
			close(piper->pipe1[0]);
			redirect (piper->infile, piper->outfile);
		}
		else
			redirect(piper->pipe1[0], piper->outfile);
	}
	else
	{
		close(piper->pipe2[1]);
		if (piper->cmd_node->stdin_redirect != NULL)
		{
			close(piper->pipe2[0]);
			redirect (piper->infile, piper->outfile);
		}
		else
			redirect(piper->pipe2[0], piper->outfile);
	}
}

void	redirect_in_child(t_piper *piper)
{
	if (piper->child_nr == 1)
		child_first(piper);
	else if (piper->child_nr == piper->fork_count)
		child_last(piper, piper->child_nr);
	else
	{
		if (piper->child_nr % 2 == 0)
			pipes_dup_close(piper->pipe1, piper->pipe2, piper);
		else
			pipes_dup_close(piper->pipe2, piper->pipe1, piper);
	}
}

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

void	child_process_pipes(t_piper *piper, t_var_list *var_list)
{
	if (piper->cmd_node->assignments != NULL)
	{
		if (add_assignments(var_list, \
			piper->cmd_node->assignments, 0) != 0)
		exit(EXIT_FAILURE); //figure out exit code
	}
	redirect_in_child(piper);
	if (ft_strncmp(piper->cmd_node->cmd[0], "echo", 5) == 0)
		exit(EXIT_FAILURE) ;
	else if (ft_strncmp(piper->cmd_node->cmd[0], "cd", 3) == 0)
		exit(EXIT_FAILURE) ;
	else if (ft_strncmp(piper->cmd_node->cmd[0], "pwd", 4) == 0)
		exit(EXIT_FAILURE) ;
	else if (ft_strncmp(piper->cmd_node->cmd[0], "cd", 3) == 0)
		exit(EXIT_FAILURE) ;
	else if (ft_strncmp(piper->cmd_node->cmd[0], "export", 7) == 0)
		exit (EXIT_FAILURE);
	else if (ft_strncmp(piper->cmd_node->cmd[0], "unset", 6) == 0)
		exit(EXIT_FAILURE) ;
	else if (ft_strncmp(piper->cmd_node->cmd[0], "env", 4) == 0)
		exit(EXIT_FAILURE) ;
	// else if (ft_strncmp(piper->cmd_node->cmd[0], "exit", 5) == 0)
	// 	builtin_exit(1);
	else
		exit(EXIT_FAILURE);
		// child_execve_process(var_list, piper->cmd_node->cmd);
	exit(EXEC_SUCCESS);
}

