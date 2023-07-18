/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piper.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarts <tmarts@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 14:41:50 by tmarts            #+#    #+#             */
/*   Updated: 2023/07/18 19:57:00 by tmarts           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

static void	init_child_data(t_parser *parser_data, t_piper *piper, int index)
{
	piper->infile = STDIN_FILENO;
	piper->outfile = STDOUT_FILENO;
	piper->child_nr = index;
	piper->cmd_node = \
		get_cmd_node(parser_data, piper->fork_count, piper->child_nr);
	if (piper->cmd_node->stdin_redirect != NULL)
		open_infiles(piper->cmd_node->stdin_redirect, &piper->infile);
	if (piper->cmd_node->stdout_redirect != NULL)
		open_outfiles(piper->cmd_node->stdout_redirect, &piper->outfile);
	return ;
}

static int	init_piper_data(t_parser *parser_data, t_piper *piper_data)
{
	piper_data->fork_count = get_fork_count(parser_data);
	piper_data->pids = (int *)ft_calloc(piper_data->fork_count, sizeof(int));
	if (!piper_data->pids)
		return (1);
	return (0);
}

static int	make_pipes(int *pipe1, int *pipe2, int child_nr)
{
	if (child_nr % 2 == 0)
	{
		if (pipe(pipe2) == -1)
			return (1);
	}
	else
	{
		if (pipe(pipe1) == -1)
			return (1);
	}	
	return (0);
}

static void	close_used_pipes_and_fds(t_piper *piper_data)
{
	if (piper_data->child_nr != 1 \
		&& piper_data->child_nr <= piper_data->fork_count)
	{
		if (piper_data->child_nr % 2 == 0)
		{
			close(piper_data->pipe1[0]);
			close(piper_data->pipe1[1]);
		}
		else
		{
			close(piper_data->pipe2[0]);
			close(piper_data->pipe2[1]);
		}
	}
	if (piper_data->cmd_node->stdin_redirect != NULL)
		close(piper_data->infile);
	if (piper_data->cmd_node->stdout_redirect != NULL)
		close(piper_data->outfile);
}

void	ft_waiting(int *pids, int nr_of_forks)
{
	t_wait	s_wait;
	int		pid_index;

	pid_index = 0;
	while (pid_index < nr_of_forks)
	{
		if (pid_index == nr_of_forks - 1)
			waitpid(pids[pid_index], &s_wait.wstatus, 0);
		else
			waitpid(pids[pid_index], NULL, 0);
		pid_index++;
	}
	if (WIFEXITED(s_wait.wstatus))
	{
		s_wait.status_code = 0;
		s_wait.status_code = WEXITSTATUS(s_wait.wstatus);
		// printf("\n\n+++++++++++ EXIT STATUS CODE:[%d] ++++++++++++++\n\n", s_wait.status_code);
		// if (s_wait.status_code != 0)
		// 	exit(s_wait.status_code); //
	}
}

// t_exec_exit_code	piper(t_parser *parser_data, t_var_list *var_list)
// {
// 	int		i;
// 	t_piper	piper;

// //if pipes then content is NULL and causes segfault
// 	if (parser_data->ast_root->content->stdin_redirect == NULL)
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
// 	if (init_piper_data(parser_data, &piper) != 0)
// 		return (EXEC_MALLOC_ERROR);
// 	i = 0;
// 	while (i <= piper.fork_count - 1)
// 	{
// 		if (piper.fork_count != 1 && i < piper.fork_count - 1)
// 		{
// 			if (make_pipes(piper.pipe1, piper.pipe2, (i + 1)) != 0)
// 				return (free(piper.pids), PIPE_ERROR);
// 		}
// 		init_child_data(parser_data, &piper, i + 1);
// 		piper.pids[i] = fork();
// 		if (piper.pids[i] == -1)
// 			return (free(piper.pids), FORK_ERROR);
// 		if (piper.pids[i] == 0)
// 			child_process(&piper, var_list);
// 		close_used_pipes(&piper);
// 		i++;
// 	}
// 	// if (piper.infile != STDIN_FILENO)
// 	// 	close(piper.infile);
// 	// if (piper.outfile != STDOUT_FILENO)
// 	// 	close(piper.outfile);
// 	ft_waiting(piper.pids, piper.fork_count);
// 	free(piper.pids);
// 	return (EXEC_SUCCESS);
// }

t_exec_exit_code	piper(t_var_list *var_list, t_parser *parser_data)
{
	int		i;
	t_piper	piper;

	if (init_piper_data(parser_data, &piper) != 0)
		return (EXEC_MALLOC_ERROR);
	i = 0;
	while (i <= piper.fork_count - 1)
	{
		if (i < piper.fork_count - 1)
		{
			if (make_pipes(piper.pipe1, piper.pipe2, (i + 1)) != 0)
				return (free(piper.pids), PIPE_ERROR);
		}
		init_child_data(parser_data, &piper, i + 1);
		piper.pids[i] = fork();
		if (piper.pids[i] == -1)
			return (free(piper.pids), FORK_ERROR);
		if (piper.pids[i] == 0)
			child_process(&piper, var_list);
		close_used_pipes_and_fds(&piper);
		i++;
	}
	ft_waiting(piper.pids, piper.fork_count);
	free(piper.pids);
	return (EXEC_SUCCESS);
}