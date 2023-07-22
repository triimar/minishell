/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunskim <eunskim@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 17:03:31 by tmarts            #+#    #+#             */
/*   Updated: 2023/07/22 21:24:20 by eunskim          ###   ########.fr       */
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

int	get_exec_data(t_minishell *data)
{
	t_parser_exit_code	parser_ret;

	parser_ret = parser(&data->parser_data, (const char *) data->p_input);
	if (parser_ret == PARSER_SYNTAX_ERROR)
		data->exit_code = 258;
	else if (parser_ret == PARSER_MALLOC_ERROR)
		data->exit_code = 1;
	else if (parser_ret == PARSER_SUCCESS)
	{
		if (expander_executor(&data->parser_data, data->var_head) == EXPANDER_SUCCESS)
			data->exit_code = 0;
		else
			data->exit_code = 1;
	}
	return (data->exit_code);
}

int	main(int argc, char **argv)
{
	t_minishell	data;

	if (argc != 1)
		return (0);
	(void)argv;
	data.var_head = NULL;
	data.p_input = NULL;
	data.exit_code = 0;
	if (initiate_var_list(&data.var_head) != 0)
		exit (EXIT_FAILURE);
	while (1)
	{
		data.p_input = readline(BLUE "eunskim_tmarts minishell % " RESET);
		if (data.p_input == NULL) /* Exit on Ctrl-D, because CTRL-D sends E0F signal and readline returns NULL when recieving an E0F */
		{
			// ft_putendl_fd("exit", 1); // maybe not the correct way to handle this... maybe 
			//free everything, stop everything			
			// break;
			// rl_redisplay();
			// ft_putendl_fd("exit", STDOUT_FILENO);
			// free(p_input);
			// rl_clear_history();
			// free_var_list(data.var_head);
			// builtin_exit(0);
		}
		if (data.p_input)
		{
			add_history(data.p_input);
			if (get_exec_data(&data) == 0)
			{
				executor(&data, &data.parser_data);
				free_ast(&data.parser_data);
			}
		}
		free(data.p_input);
	}
	rl_clear_history();
	return (0);
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

// 			if (parser(&parser_data, (const char *) p_input) == PARSER_SUCCESS)
// 			{
// 				if (expander_executor(parser_data.ast_root, data.var_head) == EXPANDER_SUCCESS)
// 				{
// 					parser_data.ast_current = parser_data.ast_root;
// 					if (parser_data.ast_root != NULL && parser_data.ast_root->content != NULL \
// 					&& parser_data.ast_root->content->cmd != NULL && \
// 					ft_strncmp(parser_data.ast_root->content->cmd[0], "exit", 5) == 0)
// 						builtin_exit(parser_data.ast_root->content->cmd[0], data.var_head, p_input, &parser_data);
// 					if (parser_data.ast_root != NULL && parser_data.ast_root->content != NULL \
// 					&& parser_data.ast_root->content->cmd != NULL && ft_strcmp("cd", parser_data.ast_root->content->cmd[0]))
// 					{
// 						builtin_cd(data.var_head, parser_data.ast_root->content->cmd);
// 						printf("\npwd: %s\n", get_value_for_key(data.var_head, "PWD"));
// 						printf("\ngetcwd says: ");
// 						builtin_pwd();
// 						printf("\noldpwd: %s\n\n", get_value_for_key(data.var_head, "OLDPWD"));
// 					}
// 					else if (parser_data.ast_root != NULL && parser_data.ast_root->content != NULL \
// 					&& parser_data.ast_root->content->cmd != NULL && ft_strcmp("echo", parser_data.ast_root->content->cmd[0]))
// 						builtin_echo(parser_data.ast_root->content->cmd);
// 					parser_test(&parser_data);
// 				}
// 				else
// 				{
// 					free_ast(&parser_data);
// 					return (1);
// 				}
// 			}
// 			else
// 				return (1);
// 		}
// 		free(p_input);
// 	}
// 	// restore_signal_handling();
// 	rl_clear_history();
// 	// set_termios(0);
// 	/*free stuff*/
// 	return (0);
// }
