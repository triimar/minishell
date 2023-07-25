/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_right_path.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarts <tmarts@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 15:47:22 by tmarts            #+#    #+#             */
/*   Updated: 2023/07/26 00:17:30 by tmarts           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	is_directory(char *path)
{
	struct stat	path_stat;

	if (stat(path, &path_stat) == -1)
	{
		internal_error_printer("stat fail");
		g_exit_code = 127;
		return (1);
	}
	if (S_ISDIR(path_stat.st_mode))
		return (announce_error(path, "Is a directory", 126), 1);
	return (0);
}

static int	get_all_paths(char ***all_paths, char **envp)
{
	int			i;

	i = 0;
	while (envp && envp[i] != 0)
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			*all_paths = ft_split((envp[i] + 5), ':');
			if (!*all_paths)
				return (1);
		}
		i++;
	}
	return (0);
}

static t_exec_exit_code	path_find_loop(char **path, char *cmd, char **all_paths)
{
	int		i;
	char	*temp_path;

	i = -1;
	while (all_paths && all_paths[++i] != NULL)
	{
		temp_path = ft_strjoin_sym(all_paths[i], cmd, '/');
		if (!temp_path)
			return (EXEC_MALLOC_ERROR);
		if (access(temp_path, F_OK) == 0)
		{
			*path = temp_path;
			return (EXEC_SUCCESS);
		}
		free(temp_path);
	}
	return (EXEC_SUCCESS);
}

t_exec_exit_code	get_right_path(t_exec *exec_data, char *command)
{
	char	**all_paths;

	all_paths = NULL;
	if (command[0] == '.' || ft_strchr(command, '/'))
	{
		exec_data->path = ft_strdup(command);
		if (exec_data->path == NULL)
			return (internal_error_printer("Malloc failed"), EXEC_MALLOC_ERROR);
		return (EXEC_SUCCESS);
	}
	if (get_all_paths(&all_paths, exec_data->envp) != 0)
		return (internal_error_printer("Malloc failed"), EXEC_MALLOC_ERROR);
	if (path_find_loop(&exec_data->path, command, all_paths) != 0)
		return (ft_free_pp(all_paths), EXEC_MALLOC_ERROR); 
	ft_free_pp(all_paths);
	return (EXEC_SUCCESS);
}