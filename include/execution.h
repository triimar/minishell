/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarts <tmarts@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 17:31:40 by tmarts            #+#    #+#             */
/*   Updated: 2023/07/10 19:43:08 by tmarts           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <stdbool.h>
# include "libft.h"
# include "parser.h"
# include "minishell.h"

typedef struct s_var_list	t_var_list;

typedef enum e_exec_exit_code
{
	EXEC_SUCCESS,
	EXEC_MALLOC_ERROR,
	PIPE_ERROR,
	FORK_ERROR,
	EXEC_FAIL,
}	t_exec_exit_code;

// typedef struct s_ast_content
// {
// 	t_redirect		*stdin_redirect;
// 	t_redirect		*stdout_redirect;
// 	t_assignment	*assignments;
// 	char			**cmd;
// }	t_ast_content;

// typedef struct s_ast
// {
// 	t_ast_content	*content;
// 	t_ast			*left;
// 	t_ast			*right;
// }	t_ast;

	// int		infile;
	// int		outfile;
	// int		forks;
	// int		pipe1[2];
	// int		pipe2[2];
		// int		*pids;
	// int		here_doc; will be handled before?

typedef struct s_exec
{
	char	**envp;
	char	*path;
}	t_exec;

t_exec_exit_code	get_envp(t_exec *s_exec, t_var_list *var_list);
t_exec_exit_code	get_right_path(t_exec *exec_data, char *command);

void				ft_free_pp_n(char **array, int str_count);
void				ft_free_pp(char **p_p);

t_exec_exit_code	test_envp_path(t_var_list *var_list, t_ast_content *cont);

#endif