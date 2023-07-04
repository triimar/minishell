/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarts <tmarts@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 16:09:17 by tmarts            #+#    #+#             */
/*   Updated: 2023/07/04 23:24:49 by tmarts           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <termios.h>
# include "libft.h"
# include "parser.h"

# define BLUE	"\033[34;1m\002"
# define RESET	"\001\e[0m\002"

extern char					**environ;

typedef struct s_var_list	t_var_list;

typedef struct s_var_list
{
	char		*key;
	char		*value;
	int			env_flag;
	t_var_list	*next;
}	t_var_list;

typedef struct s_minishell
{
	t_var_list	*var_head;
}	t_minishell;

void	builtin_exit(int exit_code);
void	handle_ctrlc(int signum);
void	signal_ctrl_c(void);
void	set_termios(int mode);

#endif