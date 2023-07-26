/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarts <tmarts@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 17:03:31 by tmarts            #+#    #+#             */
/*   Updated: 2023/07/26 19:58:47 by tmarts           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit_code;

// void restore_signal_handling()
// {
//     signal(SIGINT, SIG_DFL); // Reset signal handling for SIGINT to default
// 	signal(SIGTSTP, SIG_DFL);
// 	signal(SIGQUIT, SIG_DFL);
// }

int get_exec_data(t_minishell *data)
{
	t_parser_exit_code	parser_ret;

	parser_ret = parser(&data->parser_data, (const char *) data->p_input);
	if (parser_ret == PARSER_SYNTAX_ERROR)
		g_exit_code = 258;
	else if (parser_ret == PARSER_MALLOC_ERROR)
		g_exit_code = 1;
	else if (parser_ret == PARSER_SUCCESS)
	{
		if (expander_executor(&data->parser_data, data->var_head) == EXPANDER_SUCCESS)
			g_exit_code = 0;
		else
			g_exit_code = 1;
	}
	return (g_exit_code);
}

int	main(int argc, char **argv)
{
	t_minishell	data;

	if (argc != 1)
		return (0);
	(void)argv;
	signal(SIGTSTP, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, SIG_IGN);
	set_termios(1);
	signal_ctrl_c();
	data.var_head = NULL;
	data.p_input = NULL;
	g_exit_code = 0;
	if (initiate_var_list(&data.var_head) != 0)
		exit (EXIT_FAILURE);
	while (1)
	{
		if (isatty(fileno(stdin)))
			data.p_input = readline(BLUE "eunskim_tmarts minishell % " RESET);
		else
		{
			data.p_input = get_next_line(fileno(stdin));
			if (data.p_input)
				data.p_input[ft_strlen(data.p_input) - 1] = 0;
		}
		if (data.p_input == NULL)
		{
			ft_putendl_fd("exit", 1);
			rl_clear_history();
			free_var_list(data.var_head);
			break ;
			// rl_redisplay();
			// ft_putendl_fd("exit", STDOUT_FILENO);
			// free(p_input);
			// rl_clear_history();
			// free_var_list(data.var_head);
			// builtin_exit(0);
		}
		if (data.p_input)
		{
			if (*data.p_input)
				add_history(data.p_input);
			if (get_exec_data(&data) == 0)
			{
				executor(&data, &data.parser_data);
				free_ast(&data.parser_data);
			}
		}
		free(data.p_input);
	}
	return (g_exit_code);
}

// int	main(int argc, char **argv)
// {
// 	char		*p_input;
// 	t_parser	parser_data;
// 	t_minishell	data;

// 	// signal(SIGTSTP, SIG_IGN);
// 	// signal(SIGQUIT, SIG_IGN);
// 	// signal(SIGINT, SIG_IGN);
// 	// set_termios(1);
// 	// signal_ctrl_c();
// 	if (argc != 1)
// 		return (0);
// 	(void)argv;
// 	data.var_head = NULL;
// 	if (initiate_var_list(&data.var_head) != 0)
// 		exit (EXIT_FAILURE);
// 	while (1)
// 	{
// 		p_input = readline(BLUE "eunskim_tmarts minishell % " RESET);
// 		if (p_input == NULL) /* Exit on Ctrl-D, because CTRL-D sends E0F signal and readline returns NULL when recieving an E0F */
// 		{
// 			// ft_putendl_fd("exit", 1); // maybe not the correct way to handle this... maybe 
// 			//free everything, stop everything			
// 			// break;
// 			// rl_redisplay();
// 			// ft_putendl_fd("exit", STDOUT_FILENO);
// 			// free(p_input);
// 			// rl_clear_history();
// 			// free_var_list(data.var_head);
// 			// builtin_exit(0);
// 		}
// 		if (ft_strcmp(p_input, "var_list"))
// 			print_var_list(data.var_head);
// 		if (*p_input)
// 		{
// 			add_history(p_input);
// 		}
// 		free(p_input);
// 	}
// 	// restore_signal_handling();
// 	rl_clear_history();
// 	// set_termios(0);
// 	/*free stuff*/
// 	return (0);
// }
