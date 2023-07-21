/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_piper_data.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarts <tmarts@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 23:15:48 by tmarts            #+#    #+#             */
/*   Updated: 2023/07/21 23:30:14 by tmarts           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	init_piper_data(t_parser *parser_data, t_piper *piper)
{
	piper->fd_in_out[0] = STDIN_FILENO;
	piper->fd_in_out[1] = STDOUT_FILENO;
	piper->child_nr = 0;
	piper->fork_count = get_fork_count(parser_data);
	piper->cmd_node = NULL;
	piper->pids = (int *)ft_calloc(piper->fork_count, sizeof(int));
	if (!piper->pids)
		return (1);
	return (0);
}

int	update_child(t_parser *parser_data, t_piper *piper, int i)
{
	piper->fd_in_out[0] = STDIN_FILENO;
	piper->fd_in_out[1] = STDOUT_FILENO;
	piper->child_nr = i;
	piper->cmd_node = \
		get_cmd_node(parser_data, piper->fork_count, piper->child_nr);
	if (open_files(piper->fd_in_out, piper->cmd_node->stdin_redirect, \
									piper->cmd_node->stdout_redirect) != 0)
		return (1);
	return (0) ;
}
