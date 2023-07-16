/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunskim <eunskim@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 11:05:50 by eunskim           #+#    #+#             */
/*   Updated: 2023/07/16 13:48:13 by eunskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include <limits.h>
# include <errno.h>
# include "minishell.h"

// builtin_echo.c


// builtin_cd.c
int	builtin_cd(t_var_list *var_head, char **cmd);
int	cd_to_home(t_var_list *var_head, char *pwd);
int	cd_to_oldpwd(t_var_list *var_head, char *pwd);
int	change_value_for_key(t_var_list *var_head, char *key, char *new_value);

// builtin_pwd.c
int	builtin_pwd(void);

#endif