/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarts <tmarts@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 18:57:03 by tmarts            #+#    #+#             */
/*   Updated: 2023/07/26 19:45:44 by tmarts           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//child process ctrl+C should display on terminal ^C
void	set_termios(int mode)
{
	struct termios	ttr_settings;
	int				result;

	result = tcgetattr(STDOUT_FILENO, &ttr_settings);
	if (result < 0)
	{
		perror ("error in tcgetattr");
		return ; // deal with failures!!
	}
	if (mode == 1)
		ttr_settings.c_lflag &= ~ECHOCTL; // disable
	else
		ttr_settings.c_lflag |= ECHOCTL; //enable
	result = tcsetattr(STDOUT_FILENO, TCSANOW, &ttr_settings);
	if (result < 0)
	{
		perror ("error in tcgetattr");
		return ; // deal with failures!!
	}
}

static void	handle_ctrlc(int signum)
{
	if (signum == SIGINT)
	{
		rl_replace_line("", 0);
		write(1, "\n", 1);
		rl_on_new_line();
		rl_redisplay();
		//in child process should terminate the process 
	}
}

void	signal_ctrl_c(void)
{
	struct sigaction	sa;

	sa.sa_handler = &handle_ctrlc;
	// sa.sa_flags = RESET;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
	sa.sa_handler = &handle_ctrlc;
    if (sigaction(SIGINT, &sa, NULL) == -1)
        perror("sigaction");
}
