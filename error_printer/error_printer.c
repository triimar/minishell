/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_printer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarts <tmarts@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 17:15:50 by eunskim           #+#    #+#             */
/*   Updated: 2023/07/27 21:54:04 by tmarts           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	error_printer(char *cmd, char *arg, char *msg)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	if (arg)
	{
		ft_putstr_fd(arg, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
	}
	ft_putendl_fd(msg, STDERR_FILENO);
}

void	internal_error_printer(char *msg)
{
	ft_putstr_fd("minishell: internal error: ", STDERR_FILENO);
	ft_putendl_fd(msg, STDERR_FILENO);
}

void	announce_error(char *cmd, char *message, int code)
{
	error_printer(cmd, NULL, message);
	g_exit_code = code;
}
