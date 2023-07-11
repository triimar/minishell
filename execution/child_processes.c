/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_processes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarts <tmarts@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 19:32:12 by tmarts            #+#    #+#             */
/*   Updated: 2023/07/10 22:04:41 by tmarts           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

static void	child_middle(t_piper *piper, int child_nr)
{
	close(piper->infile);
	close(piper->outfile);
	if (child_nr % 2 == 0)
	{
		close(piper->pipe1[1]);
		close(piper->pipe2[0]);
		redirect(piper->pipe1[0], piper->pipe2[1]);
	}
	else
	{
		close(piper->pipe1[0]);
		close(piper->pipe2[1]);
		redirect(piper->pipe2[0], piper->pipe1[1]);
	}
}

static void	child_first(t_piper *piper)
{
	if (piper->fork_count == 1)
		redirect(piper->infile, piper->outfile);
	else
	{
		close(piper->outfile);
		close(piper->pipe1[0]);
		if (piper->infile < 0)
		{
			pipex_free(piper);
			exit(EXIT_FAILURE);
		}
		if (piper->here_doc == 1)
			here_doc(s_pipex);
		redirect(piper->infile, piper->pipe1[1]);
	}
}

static void	child_last(t_piper *piper, int child_nr)
{
	close(piper->infile);
	if (child_nr % 2 == 0)
	{
		close(piper->pipe1[1]);
		redirect(piper->pipe1[0], piper->outfile);
	}
	else
	{
		close(piper->pipe2[1]);
		redirect(piper->pipe2[0], piper->outfile);
	}
}

static void	child_process(t_piper *piper, t_var_list *var_list, int child_nr)
{
	t_exec	exec_data;

	exec_data.envp = NULL;
	exec_data.path = NULL;
	if (child_nr == 1)
		child_first(piper);
	else if (child_nr == piper->fork_count)
		child_last(piper, child_nr);
	else
		child_middle(piper, child_nr);
	if (get_envp(&exec_data, var_list) != 0)
		EXIT WITH MALLOC ERROR 
	// right_cmd_node = get_node(s_pipex->s_cmd_lst, child_nr);
	if (get_right_path(&exec_data, cont->cmd[0]))
		EXIT WITH MALLOC ERROR
	if (!exec_data.path)
//		free and exit code 127 - command not found with command word
	else if (access(exec_data.path, X_OK) != 0)
		// free and exit code 126 -  command not executable with command word
	execve(exec_data.path, right_cmd_node->args, exec_data.envp);
	execve_error(&exec_data);
}

void	execve_error(t_exec *exec_data)
{
	ft_putendl_fd("pipex: execve error: ", STDERR_FILENO);
	if (exec_data->path)
		free(exec_data->path);
	if (exec_data->envp)
		ft_free_pp(exec_data->envp);
	exit(EXIT_FAILURE);
}

//------the piper-forker-------
// int	pipex(t_pipex *s_pipex, char *envp[])
// {
// 	int		i;

// 	i = 0;
// 	while (i <= s_pipex->forks - 1)
// 	{
// 		if (s_pipex->forks != 1 && i < s_pipex->forks - 1)
// 		{
// 			if (make_pipes(s_pipex->pipe1, s_pipex->pipe2, (i + 1)) != 0)
// 				return (fork_pipe_error(2));
// 		}
// 		s_pipex->pids[i] = fork();
// 		if (s_pipex->pids[i] == -1)
// 			return (fork_pipe_error(3));
// 		if (s_pipex->pids[i] == 0)
// 			child_process(s_pipex, envp, (i + 1));
// 		if (s_pipex->here_doc)
// 			waitpid(s_pipex->pids[0], NULL, 0);
// 		used_pipes(s_pipex, i + 1);
// 		i++;
// 	}
// 	close(s_pipex->infile);
// 	close(s_pipex->outfile);
// 	ft_waiting(s_pipex->pids, s_pipex->forks);
// 	return (0);
// }
