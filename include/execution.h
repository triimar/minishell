/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarts <tmarts@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 17:31:40 by tmarts            #+#    #+#             */
/*   Updated: 2023/07/13 17:46:01 by tmarts           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <stdbool.h>
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

typedef struct s_piper
{
	int				infile;
	int				outfile;
	int				pipe1[2];
	int				pipe2[2];
	int				fork_count;
	int				*pids;
	int				child_nr;
	t_ast_content	*cmd_node;
}	t_piper;

typedef struct s_exec
{
	char	**envp;
	char	*path;
}	t_exec;

typedef struct s_wait
{
	int		wstatus;
	int		status_code;
}	t_wait;

void				open_infile(t_redirect *stdin_redirect, t_piper *piper);

t_exec_exit_code	piper(t_parser *parser_data, t_var_list *var_list);
void				child_process(t_piper *piper, t_var_list *var_list);

int					get_fork_count(t_parser *parser_data);
t_ast_content		*get_cmd_node(t_parser *parser_data, int fork_c, int child);

t_exec_exit_code	get_envp(t_exec *s_exec, t_var_list *var_list);
t_exec_exit_code	get_right_path(t_exec *exec_data, char *command);

void				ft_free_pp_n(char **array, int str_count);
void				ft_free_pp(char **p_p);
char				*ft_strjoin_sym(const char *s1, const char *s2, char c);
void				child_error(t_exec *exec_data, int exitcode, char *cmd);

#endif
