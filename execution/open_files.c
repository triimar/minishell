/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarts <tmarts@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 22:36:48 by tmarts            #+#    #+#             */
/*   Updated: 2023/07/21 23:12:14 by tmarts           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

static int	get_single_fd(t_redirect *current)
{
	int	redirection_fd;

	if (current->type == REDIRECT_STDOUT_APPEND)
		redirection_fd = open(current->word, O_CREAT | O_RDWR | O_APPEND, 0644);
	else if (current->type == REDIRECT_STDOUT)
		redirection_fd = open(current->word, O_CREAT | O_RDWR | O_TRUNC, 0644);
	else
		redirection_fd = open(current->word, O_RDONLY);
	if (redirection_fd < 0)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		perror(current->word);
	}
	return (redirection_fd);
}

static int	open_infiles(t_redirect *stdin_redirect, int *in_fd)
{
	t_open	redir_data;

	redir_data.current = stdin_redirect;
	redir_data.final_hdoc = here_doc_all(&redir_data.hdoc_fd, stdin_redirect);
	if (redir_data.final_hdoc != NULL && redir_data.hdoc_fd < 0)
		return (1);
	while (redir_data.current != NULL)
	{
		if (redir_data.current->type != REDIRECT_HERE_DOC)
		{
			*in_fd = get_single_fd(redir_data.current);
			if (*in_fd < 0)
			{
				if (redir_data.final_hdoc != NULL)
					close(redir_data.hdoc_fd);
				return (1);
			}	
		}
		else if (redir_data.current == redir_data.final_hdoc)
			*in_fd = redir_data.hdoc_fd;
		redir_data.current = redir_data.current->next;
		if (redir_data.current != NULL)
			close(*in_fd);
	}
	return (0);
}

static int	open_outfiles(t_redirect *stdout_redirect, int *out_fd)
{
	t_redirect	*current;

	current = stdout_redirect;
	while (current != 0)
	{
		*out_fd = get_single_fd(current);
		if (*out_fd < 0)
			return (1);
		current = current->next;
		if (current != NULL)
			close(*out_fd);
	}
	return (0);
}

int	open_files(int *fd_in_out, t_redirect *stdin, t_redirect *stdout)
{
	fd_in_out[0] = STDIN_FILENO;
	fd_in_out[1] = STDOUT_FILENO;
	if (stdin != NULL)
	{
		if (open_infiles(stdin, &fd_in_out[0]) != 0)
			return (1);
	}	
	if (stdout != NULL)
	{
		if (open_outfiles(stdout, &fd_in_out[1]) != 0)
			return (1);
	}
	return (0);
}
