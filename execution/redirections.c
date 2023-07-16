/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarts <tmarts@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 16:34:55 by tmarts            #+#    #+#             */
/*   Updated: 2023/07/16 17:53:09 by tmarts           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

// make a heredoc fuunction that returns if heredoc was found and succesfully executed
// if here_doc failed or no heredoc was found

//returns the opened and "filled" fd or -1 if error
int	here_doc(char *delimiter)
{
	int		here_doc_fd;
	char	*line;

	here_doc_fd = open("heredoc.tmp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (here_doc_fd == -1)
		return (-1);
	line = readline("> ");
	while (line && ft_strncmp(line, delimiter, ft_strlen(delimiter) + 1) != 0)
	{
		ft_putendl_fd(line, here_doc_fd);
		free(line);
		line = readline("> ");
	}
	free(line);
	close(here_doc_fd);
	here_doc_fd = open("heredoc.tmp", O_RDONLY, 0644);
	if (unlink("heredoc.tmp") == -1)
		return (-1);
	return (here_doc_fd);
}

// returns 0 if no heredoc, -1 if error, and > 0 the position of heredoc?
int	here_doc_all(int *here_doc_fd, t_redirect *stdin_redirect)
{
	t_redirect	*tmp;
	int			i;

	i = 0;
	tmp = stdin_redirect;
	while (tmp != NULL)
	{
		if (tmp->type == REDIRECT_HERE_DOC)
		{
			if (i > 0)
				close(*here_doc_fd);
			*here_doc_fd = here_doc(tmp->word);
			if (*here_doc_fd < 0)
				return (-1);
			i++;
		}
		tmp = tmp->next;
	}
	return (i);
}

void	open_infile(t_redirect *stdin_redirect, t_piper *piper)
{
	t_redirect	*tmp;
	int			here_doc_fd;
	int			here_doc_count;
	int			i;

	i = 1;
	if (stdin_redirect == NULL)
		piper->infile = STDIN_FILENO;
	tmp = stdin_redirect;
	here_doc_count = here_doc_all(&here_doc_fd, stdin_redirect); //check error
	printf("%d\n", here_doc_count);
	while (tmp != 0)
	{
		if (tmp->type == REDIRECT_HERE_DOC)
		{
			if (i == here_doc_count)
				piper->infile = here_doc_fd;
			i++;
		}	
		else
		{		
			piper->infile = open(tmp->word, O_RDONLY);
			if (piper->infile < 0)
			{
				if (here_doc_count != 0)
					close(here_doc_fd);
				ft_putstr_fd("minishell: ", STDERR_FILENO);
				perror(tmp->word);
				return ;
			}		
		}
		tmp = tmp->next;
		if (tmp != NULL)
		{
			close(piper->infile);
		}
	}
	return ;
}


