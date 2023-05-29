/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarts <tmarts@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 22:04:20 by tmarts            #+#    #+#             */
/*   Updated: 2023/01/09 17:47:22 by tmarts           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"
#include "libft.h"

char	*read_initiate(int fd)
{
	char	*buf;
	ssize_t	read_return;

	buf = malloc(BUFFER_SIZE + 1 * sizeof(char));
	if (!buf)
		return (NULL);
	read_return = read(fd, buf, BUFFER_SIZE);
	if (read_return == -1)
	{
		free (buf);
		return (NULL);
	}
	buf[read_return] = 0;
	return (buf);
}

char	*free_reader(char *buf, char *line)
{
	if (line)
		free(line);
	if (buf)
		free(buf);
	return (NULL);
}

char	*reader(int fd, char *line, char **left)
{
	char	*buf;
	ssize_t	read_return;
	size_t	len;

	buf = read_initiate(fd);
	if (!buf)
		return (free_reader(buf, line));
	read_return = ft_strlen(buf);
	while (ft_linelen(buf) == 0 && read_return != 0)
	{
		line = ft_strljoin(line, buf, read_return);
		read_return = read(fd, buf, BUFFER_SIZE);
		if (line == 0 || read_return == -1)
			return (free_reader(buf, line));
		buf[read_return] = 0;
	}
	len = ft_linelen(buf);
	line = ft_strljoin(line, buf, len);
	if (line != 0 && len != (size_t)read_return)
	{
		*left = ft_strndup(buf + len, read_return - len + 1);
		if (!*left)
			return (free_reader(buf, line));
	}	
	return (free(buf), line);
}

char	*null_leftovers(char **left)
{
	free(*left);
	*left = NULL;
	return (NULL);
}

char	*get_next_line(int fd)
{
	static char	*left[1024];
	char		*line;
	size_t		len;

	if (fd < 0 || fd > 1024)
		return (NULL);
	if (left[fd] == NULL)
		return (reader(fd, NULL, &(left[fd])));
	len = (ft_linelen(left[fd]));
	if (len > 0)
	{
		line = ft_strndup(left[fd], len);
		if (line == 0)
			return (null_leftovers(&(left[fd])));
		if (len == ft_strlen(left[fd]))
			null_leftovers(&(left[fd]));
		else
			ft_strlcpy(left[fd], left[fd] + len, ft_strlen(left[fd]) - len + 1);
		return (line);
	}
	line = ft_strndup(left[fd], ft_strlen(left[fd]));
	null_leftovers(&(left[fd]));
	if (line == 0)
		return (NULL);
	return (reader(fd, line, &(left[fd])));
}
