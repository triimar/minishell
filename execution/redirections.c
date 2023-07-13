/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarts <tmarts@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 16:34:55 by tmarts            #+#    #+#             */
/*   Updated: 2023/07/13 17:44:51 by tmarts           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"


void	open_infile(t_redirect *stdin_redirect, t_piper *piper)
{
	t_redirect	*tmp;

	tmp = stdin_redirect;
	if (stdin_redirect == NULL)
		piper->infile = STDIN_FILENO;
	while (tmp != 0)
	{
		piper->infile = open(tmp->word, O_RDONLY);
		if (piper->infile < 0)
		{
			ft_putstr_fd("minishell: ", STDERR_FILENO);
			perror(tmp->word);
			return ;
		}
		tmp = tmp->next;
		if (tmp != NULL)
			close(piper->infile);
	}
	return ;
}

// t_parser_exit_code	open_infile(t_redirect *stdin_redirect, t_piper *piper)
// {
// 	// if (ft_str_same(infile, "here_doc", ft_strlen(infile)) == 0)
// 	// {
// 	// 	s_pipex->here_doc = 1;
// 	// 	s_pipex->infile = STDIN_FILENO;
// 	// 	s_pipex->outfile = open(outfile, O_CREAT | O_RDWR | O_APPEND, 0644);
// 	// }
// 	t_redirect	*tmp;
// 	int			i;

// 	tmp = stdin_redirect;
// 	if (stdin_redirect == NULL)
// 		piper->infile = STDIN_FILENO;
// 	if (tmp != 0)
// 	{
// 		piper->infile = open(tmp->word, O_RDONLY);
// 		if (piper->infile < 0)
// 		{
// 			ft_putstr_fd("minishell: ", STDERR_FILENO);
// 			perror(tmp->word);
// 		}
		
// 	}
// 	// 	s_pipex->outfile = open(outfile, O_CREAT | O_RDWR | O_TRUNC, 0644);
// 	// }
// 	// if (s_pipex->outfile < 0)
// 	// {
// 	// 	ft_putstr_fd("pipex: ", STDERR_FILENO);
// 	// 	perror(outfile);
// 	// 	exit (EXIT_FAILURE);
// 	// }
// }
