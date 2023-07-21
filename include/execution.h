/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarts <tmarts@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 17:31:40 by tmarts            #+#    #+#             */
/*   Updated: 2023/07/21 01:32:18 by tmarts           ###   ########.fr       */
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
typedef struct s_minishell	t_minishell;

typedef enum e_exec_exit_code
{
	EXEC_SUCCESS,
	EXEC_FAIL,
	EXEC_MALLOC_ERROR,
	PIPE_ERROR,
	FORK_ERROR,
}	t_exec_exit_code;

typedef struct s_in_redir
{
	t_redirect	*current;
	t_redirect	*final_hdoc;
	int			hdoc_fd;
}	t_in_redir;

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

t_exec_exit_code	add_to_var_list(t_var_list *var_list, \
											t_assignment *assign, int flag);

int					open_infiles(t_redirect *stdin_redirect, int *in_fd);
int					open_outfiles(t_redirect *stdin_redirect, int *in_fd);
t_redirect			*here_doc_all(int *here_doc_fd, t_redirect *stdin_redirect);
int					redirect_main(int *stdin_save, t_redirect *stdin_redirect, \
							int *stdout_save, t_redirect *stdout_redirect);
void				restore_redirect(int stdin_save, int stdout_save);

t_exec_exit_code	executor(t_minishell *ms_data, t_parser *parser_data);
t_exec_exit_code	piper(t_var_list *var_list, t_parser *parser_data);
void				child_process_pipes(t_piper *piper, t_var_list *var_list);
void				child_execve_process(t_var_list *var_list, char **cmd);

void				ft_waiting(int *pids, int nr_of_forks);

int					get_fork_count(t_parser *parser_data);
t_ast_content		*get_cmd_node(t_parser *parser_data, int fork_c, int child);

t_exec_exit_code	get_envp(t_exec *s_exec, t_var_list *var_list);
t_exec_exit_code	get_right_path(t_exec *exec_data, char *command);

void				ft_free_pp_n(char **array, int str_count);
void				ft_free_pp(char **p_p);
char				*ft_strjoin_sym(const char *s1, const char *s2, char c);

void				child_error(t_exec *exec_data, int exitcode, char *cmd);

void				builtin_error_printer(char *cmd, char *arg, char *msg);
void				internal_error_printer(char *msg);

#endif
