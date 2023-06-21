/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarts <tmarts@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 20:06:08 by tmarts            #+#    #+#             */
/*   Updated: 2023/06/11 22:17:30 by tmarts           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	builtin_exit(int exit_code)
{
	if (exit_code < 0 || exit_code > 255)
		exit_code = exit_code % 256;
	// ft_putendl_fd("exit", 1);
	exit (exit_code);
}
