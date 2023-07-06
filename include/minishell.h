/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunskim <eunskim@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 16:09:17 by tmarts            #+#    #+#             */
/*   Updated: 2023/07/06 13:35:40 by eunskim          ###   ########.fr       */
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
# include <stdbool.h>
# include "libft.h"
# include "parser.h"

# define BLUE	"\033[34;1m\002"
# define RESET	"\001\e[0m\002"

extern char					**environ;

typedef struct s_var_list	t_var_list;

typedef enum e_ms_exit_code
{
	MINISHELL_SUCCESS,
	MS_MALLOC_ERROR
}	t_ms_exit_code;

typedef struct s_var_list
{
	char		*key;
	char		*value;
	bool		env_flag;
	t_var_list	*next;
}	t_var_list;

typedef struct s_minishell
{
	t_var_list	*var_head;
}	t_minishell;

void				builtin_exit(int exit_code);

t_ms_exit_code		initiate_var_list(t_var_list **var_list);
void				free_var_list(t_var_list *var_list);
void				print_var_list(t_var_list *var_list);

char				*ft_strdup_pt(const char *start, char *delimiter);
void				ft_lstadd_back_ms(t_var_list **var_list, t_var_list *new);

// void	handle_ctrlc(int signum);
// void	signal_ctrl_c(void);
// void	set_termios(int mode);

#endif