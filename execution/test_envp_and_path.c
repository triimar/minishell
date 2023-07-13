/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_envp_and_path.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarts <tmarts@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 17:54:50 by tmarts            #+#    #+#             */
/*   Updated: 2023/07/10 21:06:19 by tmarts           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

t_exec_exit_code	test_envp_path(t_var_list *var_list, t_ast_content *cont)
{
	t_exec	exec_data;
	int		i;

	exec_data.envp = NULL;
	exec_data.path = NULL;
	if (get_envp(&exec_data, var_list) != 0)
		return (EXEC_MALLOC_ERROR);
	i = 0;
	printf("\n\n------- ENVP for execve ---------\n\n");
	while (exec_data.envp && exec_data.envp[i] != NULL)
	{
		printf("%d - [%s]\n", i, exec_data.envp[i]);
		i++;
	}
	get_right_path(&exec_data, cont->cmd[0]);
	printf("\nPATH FOUND:[%s]\n", exec_data.path);
	ft_free_pp_n(exec_data.envp, i);
	free(exec_data.path);
	return (EXEC_SUCCESS);
}