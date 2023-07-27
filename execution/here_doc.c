/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarts <tmarts@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 16:34:55 by tmarts            #+#    #+#             */
/*   Updated: 2023/07/27 22:49:03 by tmarts           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

static int	ft_str_same(const char *s1, const char *s2, size_t len_s1)
{
	if (len_s1 == 0)
		return (0);
	if (ft_strlen(s2) != len_s1)
		return (1);
	while (len_s1 > 0 && *s1 == *s2 && *s1 != 0 && *s2 != 0)
	{
		len_s1--;
		s1++;
		s2++;
	}
	if (len_s1 == 0 && *s2 == 0)
		return (0);
	return (1);
}

static int	here_doc(char *delimiter)
{
	int		here_doc_fd;
	char	*line;

	here_doc_fd = open("heredoc.tmp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (here_doc_fd == -1)
		return (announce_error("heredoc", "Failed to open file", 2), -1);
	// ft_putstr_fd("> ", STDOUT_FILENO);
	line = get_next_line(STDIN_FILENO);
	while (line && ft_str_same(line, delimiter, (ft_strlen(line) - 1)) != 0)
	{
		ft_putstr_fd(line, here_doc_fd);
		free(line);
		// ft_putstr_fd("> ", STDOUT_FILENO);
		line = get_next_line(STDIN_FILENO);
	}
	free(line);
	close(here_doc_fd);
	here_doc_fd = open("heredoc.tmp", O_RDONLY, 0644);
	if (here_doc_fd == -1)
		return (announce_error("heredoc", "Failed to open file", 2), -1);
	if (unlink("heredoc.tmp") == -1)
		return (announce_error("heredoc", "Failed to unlink", 2), -1);
	return (here_doc_fd);
}

t_redirect	*here_doc_all(int *here_doc_fd, t_redirect *stdin_redirect)
{
	t_redirect	*tmp;
	t_redirect	*heredoc_node;
	int			i;

	i = 0;
	heredoc_node = NULL;
	tmp = stdin_redirect;
	while (tmp != NULL)
	{
		if (tmp->type == REDIRECT_HERE_DOC)
		{
			if (i > 0)
				close(*here_doc_fd);
			heredoc_node = tmp;
			*here_doc_fd = here_doc(tmp->word);
			if (*here_doc_fd < 0)
				return (heredoc_node);
			i++;
		}
		tmp = tmp->next;
	}
	return (heredoc_node);
}
