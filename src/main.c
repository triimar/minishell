/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunskim <eunskim@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 17:03:31 by tmarts            #+#    #+#             */
/*   Updated: 2023/07/13 14:18:42 by eunskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// lexer/parser TODO : error handling (error message, exit code), more testing

// void restore_signal_handling()
// {
//     signal(SIGINT, SIG_DFL); // Reset signal handling for SIGINT to default
// 	signal(SIGTSTP, SIG_DFL);
// 	signal(SIGQUIT, SIG_DFL);
// }

int	main(int argc, char **argv)
{
	char		*p_input;
	t_parser	parser_data;
	t_minishell	data;

	// signal(SIGTSTP, SIG_IGN);
	// signal(SIGQUIT, SIG_IGN);
	// signal(SIGINT, SIG_IGN);
	// set_termios(1);
	// signal_ctrl_c();
	if (argc != 1)
		return (0);
	(void)argv;
	data.var_head = NULL;
	if (initiate_var_list(&data.var_head) != 0)
		exit (EXIT_FAILURE);
	while (1)
	{
		p_input = readline(BLUE "eunskim_tmarts minishell % " RESET);
		if (p_input == NULL) /* Exit on Ctrl-D, because CTRL-D sends E0F signal and readline returns NULL when recieving an E0F */
		{
			// ft_putendl_fd("exit", 1); // maybe not the correct way to handle this... maybe 
			//free everything, stop everything
			
			// break;
			rl_redisplay();
			ft_putendl_fd("exit", STDOUT_FILENO);
			free(p_input);
			rl_clear_history();
			free_var_list(data.var_head);
			builtin_exit(0);
		}
		if (ft_strcmp(p_input, "exit"))
		{
			free(p_input);
			rl_clear_history();
			free_var_list(data.var_head);
			// system("leaks minishell");
			builtin_exit(0);
		}
		if (ft_strcmp(p_input, "var_list"))
			print_var_list(data.var_head);
		if (*p_input)
		{
			add_history(p_input);
			// expander_test(data.var_head);
			if (parser(&parser_data, (const char *) p_input) == PARSER_SUCCESS)
			{
				if (expander_executor(parser_data.ast_root, data.var_head) == EXPANDER_SUCCESS)
					parser_test(&parser_data);
				else
				{
					free_ast(&parser_data);
					return (1);
				}
			}
			else
				return (1);
		}
		free(p_input);
	}
	// restore_signal_handling();
	rl_clear_history();
	// set_termios(0);
	/*free stuff*/
	return (0);
}
