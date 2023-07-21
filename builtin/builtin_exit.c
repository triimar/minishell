/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarts <tmarts@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 14:34:18 by tmarts            #+#    #+#             */
/*   Updated: 2023/07/21 15:28:57 by tmarts           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_on_exit(t_minishell *ms_data)
{
	if (ms_data->p_input)
		free(ms_data->p_input);
	if (ms_data->var_head)
		free_var_list(ms_data->var_head);
	if (ms_data->parser_data)
		free_ast(ms_data->parser_data);
	rl_clear_history();
}

static int	get_arg_count(char **cmd)
{
	int	arg_count;

	arg_count = 0;
	while (cmd && *(cmd + arg_count) != NULL)
		arg_count++;
	return (arg_count);
}

int	builtin_exit(t_minishell *ms_data, char **cmd)
{
	int	exit_code;
	int	arg_count;

	ft_putendl_fd("exit", 1);
	arg_count = get_arg_count(cmd);
	if (arg_count == 1)
		exit_code = 0;
	else if (arg_count == 2)
	{
		if (ft_atoi_secure(cmd[1], &exit_code) != 0)
		{
			builtin_error_printer("exit", cmd[1], "numeric argument required");
			exit_code = 255;
		}
	}
	else
	{
		builtin_error_printer("exit", NULL, "too many arguments");
		return (1);
	}
	if (exit_code < 0 || exit_code > 255)
		exit_code = exit_code % 256;
	free_on_exit(ms_data);
	exit (exit_code);
}
