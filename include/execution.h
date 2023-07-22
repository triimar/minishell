/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarts <tmarts@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 17:31:40 by tmarts            #+#    #+#             */
/*   Updated: 2023/07/22 17:28:33 by tmarts           ###   ########.fr       */
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

typedef struct s_open
{
	t_redirect	*current;
	t_redirect	*final_hdoc;
	int			hdoc_fd;
}	t_open;

typedef struct s_piper
{
	int				fd_in_out[2];
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

// execution.c
t_exec_exit_code	executor(t_minishell *ms_data, t_parser *parser_data);

// assignments.c
t_exec_exit_code	add_assignments(t_var_list *var_list, \
											t_assignment *assign, int flag);
t_exec_exit_code	add_to_var_list(t_var_list *var_list, \
											char *str, int flag);

// open_files.c
int					open_files(int *fds, t_redirect *stdin, t_redirect *stdout);

// here_doc.c
t_redirect			*here_doc_all(int *here_doc_fd, t_redirect *stdin_redirect);

// redirections.c
void				redirect(int in_fd, int out_fd);
void				restore_redirect(int stdin_save, int stdout_save);

// builtin_execution.c
int					is_builtin(char *cmd);
int					run_builtin(t_var_list *var_list, char **cmd);

// execution_utils.c
void				ft_free_pp(char **p_p);
void				ft_free_pp_n(char **array, int str_count);
char				*ft_strjoin_sym(const char *s1, const char *s2, char c);
int					get_fork_count(t_parser *parser_data);
t_ast_content		*get_cmd_node(t_parser *parser_data, int fork_c, int child);

//init_piper_data.c
int					init_piper_data(t_parser *parser_data, t_piper *piper);
int					update_child(t_parser *parser_data, t_piper *piper, int i);

// piper.c
t_exec_exit_code	piper(t_minishell *ms_data, t_parser *parser_data);
void				ft_waiting(int *pids, int nr_of_forks, int *exit_code);

//child_processes.c
void				child_execve_process(t_minishell *ms_data, char **cmd);
void				child_with_pipes(t_minishell *ms_data, t_piper *piper);

//redirections_in_child.c
void				redirect_in_child(t_piper *piper);

// get_envp.c & get_right_path.c
t_exec_exit_code	get_envp(t_exec *s_exec, t_var_list *var_list);
t_exec_exit_code	get_right_path(t_exec *exec_data, char *command);

// ../error_printer/error_printer.c
void				error_printer(char *cmd, char *arg, char *msg);
void				internal_error_printer(char *msg);

#endif
