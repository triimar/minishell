/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarts <tmarts@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 20:06:08 by tmarts            #+#    #+#             */
/*   Updated: 2023/07/19 22:10:03 by tmarts           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	atoi_negative(char *c)
{
	if (*c == '-')
		return (-1);
	else
		return (1);
}

static int	ft_atoi_extra(const char *str, int *data)
{
	int		intvalue;
	int		neg_pos;
	char	*chr;

	intvalue = 0;
	neg_pos = 1;
	chr = (char *)str;
	while (chr && (*chr == ' ' || *chr == '\t'))
		chr++;
	if (chr && (*chr == '-' || *chr == '+') && *(chr + 1) != '\0')
		neg_pos = atoi_negative(chr++);
	while (*chr != '\0')
	{
		if (!(*chr >= '0' && *chr <= '9'))
			return (EXIT_FAILURE);
		if (neg_pos == -1 && intvalue * -10 - (*chr - '0') == INT_MIN)
			return (INT_MIN); //wtf is this, needs fix!
		if (intvalue > (INT_MAX - (*chr - '0')) / 10)
			return (EXIT_FAILURE);
		intvalue = intvalue * 10 + (*chr - '0');
		chr++;
	}
	*data = (int)(intvalue * neg_pos);
	return (EXIT_SUCCESS);
}

void	free_on_exit(t_var_list *var_list, char *p_input, t_parser *parser_data)
{
	if (p_input)
		free(p_input);
	if (var_list)
		free_var_list(var_list);
	free_ast(parser_data);
	rl_clear_history();
}

int	get_arg_count(char **cmd)
{
	int	arg_count;

	arg_count = 0;
	while (cmd && *(cmd + arg_count) != NULL)
		arg_count++;
	return (arg_count);
}

void	builtin_exit(char **cmd, t_var_list *var_list, char *p_input, \
													t_parser *parser_data)
{
	int	exit_code;
	int	arg_count;

	ft_putendl_fd("exit", 1);
	arg_count = get_arg_count(cmd);
	if (arg_count == 1)
		exit_code = 0;
	else if (arg_count == 2)
	{
		if (ft_atoi_extra(cmd[1], &exit_code) != 0)
		{
			builtin_error_printer("exit", cmd[1], "numeric argument required");
			exit_code = 255;
		}
	}
	else
	{
		//set exit code to 1 but no exit
		return (builtin_error_printer("exit", NULL, "too many arguments"));
	}
	if (exit_code < 0 || exit_code > 255)
		exit_code = exit_code % 256;
	free_on_exit(var_list, p_input, parser_data);
	exit (exit_code);
}
