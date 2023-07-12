/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piper.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarts <tmarts@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 14:41:50 by tmarts            #+#    #+#             */
/*   Updated: 2023/07/12 19:10:25 by tmarts           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

static void	init_child_data(t_parser *parser_data, t_piper *piper, int index)
{
	piper->child_nr = index;
	piper->cmd_node = \
		get_cmd_node(parser_data, piper->fork_count, piper->child_nr);
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

static void	close_used_pipes(t_piper *piper_data)
{
	if (piper_data->fork_count != 1 && piper_data->child_nr != 1 && \
		piper_data->child_nr <= piper_data->fork_count)
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
}

static void	ft_waiting(int *pids, int nr_of_forks)
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
		printf("\n\n+++++++++++ EXIT STATUS CODE:[%d] ++++++++++++++\n\n", s_wait.status_code);
		// if (s_wait.status_code != 0)
		// 	exit(s_wait.status_code); //
	}
}

t_exec_exit_code	piper(t_parser *parser_data, t_var_list *var_list)
{
	int		i;
	t_piper	piper;

	piper.infile = STDIN_FILENO; //
	piper.outfile = STDOUT_FILENO;//
	if (init_piper_data(parser_data, &piper) != 0)
		return (EXEC_MALLOC_ERROR);
	i = 0;
	while (i <= piper.fork_count - 1)
	{
		if (piper.fork_count != 1 && i < piper.fork_count - 1)
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
		close_used_pipes(&piper);
		i++;
	}
	// close(piper.infile);
	// close(piper.outfile); //restore stdin stdout
	ft_waiting(piper.pids, piper.fork_count);
	free(piper.pids);
	return (EXEC_SUCCESS);
}
