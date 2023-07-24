/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunskim <eunskim@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 11:05:50 by eunskim           #+#    #+#             */
/*   Updated: 2023/07/24 18:10:07 by eunskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include <limits.h>
# include <errno.h>
# include <sys/stat.h>
# include "minishell.h"

typedef struct s_minishell	t_minishell;

// builtin_echo.c
int		builtin_echo(char **cmd);
int		builtin_echo_strjoin(char **cmd, int cnt, int option_n);
int		check_option_n(char **arg);

// builtin_cd.c
int		builtin_cd(t_var_list *var_head, char **cmd);
int		execute_cd(t_var_list *var_head, char **cmd);
int		cd_with_path(t_var_list *var_head, char **cmd, char *pwd);
int		cd_to_home(t_var_list *var_head, char *pwd);
int		cd_to_oldpwd(t_var_list *var_head, char *pwd);

// builtin_exit.c & builtin_exit_utils.c
int		builtin_exit(t_minishell *ms_data, char **cmd);
int		ft_atoi_secure(const char *str, int *data);
void	free_on_exit(t_minishell *ms_data);

// builtin_pwd.c
int		builtin_pwd(void);

// builtin_env.c
int		builtin_env(t_var_list *var_list);

// builtin_export.c
int		builtin_export(t_var_list *var_head, char **cmd);

// builtin_utils.c
int		get_arg_count(char **cmd);
int		change_value_for_key(t_var_list *var_head, char *key, char *new_value);
bool	check_if_in_var_list(t_var_list *var_head, char *key);
char	*get_value_for_key(t_var_list *var_head, const char *key);

#endif