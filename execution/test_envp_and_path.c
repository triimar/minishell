/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_envp_and_path.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarts <tmarts@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 17:54:50 by tmarts            #+#    #+#             */
/*   Updated: 2023/07/09 20:45:13 by tmarts           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

t_exec_exit_code	test_envp_and_path(t_var_list *var_list, t_ast_content *content)
{
	t_exec	exec_data;
	char	*the_path;
	int		i;

	exec_data.envp = NULL;
	exec_data.all_paths = NULL;
	if (get_envp(&exec_data, var_list) != 0)
		return (EXEC_MALLOC_ERROR);
	i = 0;
	while (exec_data.envp && exec_data.envp[i] != NULL)
	{
		printf("%d - [%s]\n", i, exec_data.envp[i]);
		i++;
	}
	printf("\n");
	ft_free_ptpt(exec_data.envp, i);
	if (get_all_paths(&exec_data, var_list) != 0)
		return (EXEC_MALLOC_ERROR);
	i = 0;
	while (exec_data.all_paths && exec_data.all_paths[i] != NULL)
	{
		printf("%d - [%s]\n", i, exec_data.all_paths[i]);
		i++;
	}
	the_path = get_right_path(content->cmd[0], exec_data.all_paths);
	printf("\n[%s]\n", the_path);
	ft_free_ptpt(exec_data.all_paths, i);
	free(the_path);
	return (EXEC_SUCESS);
}
