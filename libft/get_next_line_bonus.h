/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarts <tmarts@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 22:04:24 by tmarts            #+#    #+#             */
/*   Updated: 2023/01/09 17:42:36 by tmarts           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <stdlib.h>
# include <unistd.h>
# include "libft.h"

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 22
# endif

/*get_next_line_bonus*/
char	*read_initiate(int fd);
char	*free_reader(char *buf, char *line);
char	*reader(int fd, char *line, char **leftovers);
char	*null_leftovers(char **leftovers);
char	*get_next_line(int fd);

/*utils_bonus*/
size_t	ft_linelen(const char *str);
char	*ft_strljoin(char *s1, char *s2, int len_s2);
char	*ft_strndup(const char *str, size_t len);

#endif