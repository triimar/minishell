/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_right_path.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarts <tmarts@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 15:47:22 by tmarts            #+#    #+#             */
/*   Updated: 2023/07/09 20:42:55 by tmarts           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

t_exec_exit_code	get_all_paths(t_exec *s_exec, t_var_list *var_list)
{
	t_var_list	*cur_node;
	int			i;

	i = 0;
	cur_node = var_list;
	while (cur_node != NULL)
	{
		if (ft_strncmp(cur_node->key, "PATH", 4) == 0)
		{
			if (cur_node->value == NULL)
				return (0); /*no path in env*/
			s_exec->all_paths = ft_split(cur_node->value, ':');
			if (!s_exec->all_paths)
				return (EXEC_MALLOC_ERROR);
			return (0);
		}
		cur_node = cur_node->next;
	}
	return (EXEC_SUCESS);
}

static char	*path_find_loop(char *command, char **all_paths) // if returns NULL no path or malloc fail...?
{
	int		i;
	char	*temp_path;

	i = -1;
	while (all_paths && all_paths[++i] != NULL)
	{
		temp_path = ft_strjoin_sym(all_paths[i], command, '/');
		if (!temp_path)
			return (NULL);
		if (access(temp_path, F_OK) == 0)
			return (temp_path);
		free(temp_path);
	}
	return (NULL);
}

char	*get_right_path(char *command, char **all_paths)
{
	if (!command)
		return (NULL);
	if (access(command, F_OK) == 0 && (command[0] == '.'
			|| command[0] == '/' || ft_strchr(command + 1, '/')))
		return (command);
	if (all_paths)
		return (path_find_loop(command, all_paths));
	// if (!all_paths)
	// 	return (no_env_path(command)); //?
	return (NULL);
}