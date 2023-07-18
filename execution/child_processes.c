/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_processes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarts <tmarts@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 19:32:12 by tmarts            #+#    #+#             */
/*   Updated: 2023/07/18 20:03:48 by tmarts           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

// static void	redirect(int in_fd, int out_fd)
// {
// 	dup2(in_fd, STDIN_FILENO);
// 	close(in_fd);
// 	dup2(out_fd, STDOUT_FILENO);
// 	close(out_fd);
// }

static void	redirect(int in_fd, int out_fd)
{
	if (in_fd != STDIN_FILENO)
	{
		dup2(in_fd, STDIN_FILENO);
		close(in_fd);
	}
	if (out_fd != STDOUT_FILENO)
	{
		dup2(out_fd, STDOUT_FILENO);
		close(out_fd);
	}
}

static void	child_middle(t_piper *piper, int child_nr)
{
	if (child_nr % 2 == 0)
	{
		close(piper->pipe1[1]);
		close(piper->pipe2[0]);
		if (piper->cmd_node->stdin_redirect != NULL)
		{
			close(piper->pipe1[0]);
			dup2(piper->infile, STDIN_FILENO);
		}
		else
			dup2(piper->pipe1[0], STDIN_FILENO);
		if (piper->cmd_node->stdout_redirect != NULL)
		{
			close(piper->pipe2[1]);
			dup2(piper->outfile, STDOUT_FILENO);
		}
		else
			dup2(piper->pipe2[1], STDOUT_FILENO);
	}
	else
	{
		close(piper->pipe1[0]);
		close(piper->pipe2[1]);
		if (piper->cmd_node->stdin_redirect != NULL)
		{
			close(piper->pipe2[0]);
			dup2(piper->infile, STDIN_FILENO);
		}
		else
			dup2(piper->pipe2[0], STDIN_FILENO);
		if (piper->cmd_node->stdout_redirect != NULL)
		{
			close(piper->pipe1[1]);
			dup2(piper->outfile, STDOUT_FILENO);
		}
		else
			dup2(piper->pipe1[1], STDOUT_FILENO);
	}
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

// static void	child_redirections(t_piper *piper, int child_nr)
// {
// 		if (parser_data->ast_root->content->stdin_redirect == NULL)
// 		piper.infile = STDIN_FILENO;
// 	else
// 	{
// 		open_infiles(parser_data->ast_root->content->stdin_redirect, &piper.infile);
// 		if (piper.infile < 0)
// 			return (EXEC_FAIL);
// 	}
// 	if (parser_data->ast_root->content->stdout_redirect == NULL)
// 		piper.outfile = STDOUT_FILENO;
// 	else
// 	{
// 		open_outfiles(parser_data->ast_root->content->stdout_redirect, &piper.outfile);
// 		if (piper.outfile < 0)
// 			return (EXEC_FAIL);
// 	}
// 	if (child_nr % 2 == 0)
// 	{
// 		close(piper->pipe1[1]);
// 		close(piper->pipe2[0]);
// 		redirect(piper->pipe1[0], piper->pipe2[1]);
// 	}
// 	else
// 	{
// 		close(piper->pipe1[0]);
// 		close(piper->pipe2[1]);
// 		redirect(piper->pipe2[0], piper->pipe1[1]);
// 	}
// }

void	child_process(t_piper *piper, t_var_list *var_list)
{
	t_exec	exec_data;

	exec_data.envp = NULL;
	exec_data.path = NULL;
	if (piper->cmd_node->cmd == NULL)
		exit (0);
	if (piper->child_nr == 1)
		child_first(piper);
	else if (piper->child_nr == piper->fork_count)
		child_last(piper, piper->child_nr);
	else
		child_middle(piper, piper->child_nr);
	if (get_envp(&exec_data, var_list) != 0)
		exit(EXIT_FAILURE);
	if (get_right_path(&exec_data, piper->cmd_node->cmd[0]) != 0)
		child_error(&exec_data, 1, piper->cmd_node->cmd[0]);
	if (!exec_data.path)
		child_error(&exec_data, 127, piper->cmd_node->cmd[0]);
	if (access(exec_data.path, X_OK) != 0)
		child_error(&exec_data, 128, piper->cmd_node->cmd[0]);
	execve(exec_data.path, piper->cmd_node->cmd, exec_data.envp);
	child_error(&exec_data, -1, piper->cmd_node->cmd[0]);
}