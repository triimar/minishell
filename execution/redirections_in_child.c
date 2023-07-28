/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_in_child.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarts <tmarts@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 23:45:09 by tmarts            #+#    #+#             */
/*   Updated: 2023/07/27 22:33:27 by tmarts           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

static void	middle_dup_close(int pipe_read[], int pipe_write[], t_piper *piper)
{
	close(pipe_read[1]);
	close(pipe_write[0]);
	if (piper->cmd_node->stdin_redirect != NULL)
	{
		close(pipe_read[0]);
		dup2(piper->fd_in_out[0], STDIN_FILENO);
	}
	else
		dup2(pipe_read[0], STDIN_FILENO);
	if (piper->cmd_node->stdout_redirect != NULL)
	{
		close(pipe_write[1]);
		dup2(piper->fd_in_out[1], STDOUT_FILENO);
	}
	else
		dup2(pipe_write[1], STDOUT_FILENO);
}

static void	child_first_redir(t_piper *piper)
{
	close(piper->pipe1[0]);
	if (piper->cmd_node->stdout_redirect != NULL)
	{
		close(piper->pipe1[1]);
		redirect(piper->fd_in_out[0], piper->fd_in_out[1]);
	}
	redirect(piper->fd_in_out[0], piper->pipe1[1]);
}

static void	child_last_redir(t_piper *piper, int child_nr)
{
	if (child_nr % 2 == 0)
	{
		close(piper->pipe1[1]);
		if (piper->cmd_node->stdin_redirect != NULL)
		{
			close(piper->pipe1[0]);
			redirect (piper->fd_in_out[0], piper->fd_in_out[1]);
		}
		else
			redirect(piper->pipe1[0], piper->fd_in_out[1]);
	}
	else
	{
		close(piper->pipe2[1]);
		if (piper->cmd_node->stdin_redirect != NULL)
		{
			close(piper->pipe2[0]);
			redirect (piper->fd_in_out[0], piper->fd_in_out[1]);
		}
		else
			redirect(piper->pipe2[0], piper->fd_in_out[1]);
	}
}

void	redirect_in_child(t_piper *piper)
{	
	if (piper->child_nr == 1)
		child_first_redir(piper);
	else if (piper->child_nr == piper->fork_count)
		child_last_redir(piper, piper->child_nr);
	else
	{
		if (piper->child_nr % 2 == 0)
			middle_dup_close(piper->pipe1, piper->pipe2, piper);
		else
			middle_dup_close(piper->pipe2, piper->pipe1, piper);
	}
}
