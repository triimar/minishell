/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_right_path.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarts <tmarts@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 15:47:22 by tmarts            #+#    #+#             */
/*   Updated: 2023/07/12 17:34:30 by tmarts           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

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
			// i = 0;
			// printf("\n\n------- ALL POSSIBLE PATHS ---------\n\n");
			// while (all_paths[0][i] != NULL)
			// {
			// 	printf("%d - [%s]\n", i, all_paths[0][i]);
			// 	i++;
			// }
			// printf("\n\n-----------------------------------");
			// return (0);
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
	if (!command) // empty string - result cmd not found exit code 127
		return (EXEC_FAIL); //is it possible to reach this point w/o command?
	if (access(command, F_OK) == 0 && (command[0] == '.'
			|| command[0] == '/' || ft_strchr(command + 1, '/')))
	{
		exec_data->path = ft_strdup(command);
		return (EXEC_SUCCESS);
	}
	if (get_all_paths(&all_paths, exec_data->envp) != 0)
		return (EXEC_MALLOC_ERROR);
	if (!all_paths) //what happens if path is not in envp?
	{
		// (no_env_path(command)); //? return exit code 126 for no such file or directory
		return (EXEC_FAIL);
	}
	if (path_find_loop(&exec_data->path, command, all_paths) != 0)
		return (ft_free_pp(all_paths), EXEC_MALLOC_ERROR); 
	// if (!exec_data->path)
		// return exit code 127
  	// if (access(path, X_OK) != 0)
	// 	return exit code 126
	ft_free_pp(all_paths);
	return (EXEC_SUCCESS);
}