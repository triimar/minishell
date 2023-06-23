/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunskim <eunskim@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 16:09:17 by tmarts            #+#    #+#             */
/*   Updated: 2023/06/23 12:11:47 by eunskim          ###   ########.fr       */
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

void	builtin_exit(int exit_code);
void	handle_ctrlc(int signum);
void	signal_ctrl_c(void);
void	set_termios(int mode);

#endif