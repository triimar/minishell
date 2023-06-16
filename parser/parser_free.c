/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_free.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunskim <eunskim@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 12:53:09 by eunskim           #+#    #+#             */
/*   Updated: 2023/06/16 13:38:26 by eunskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parser.h"

void	free_all_data()
{

}

void	free_assignment_list()
{
	
}

void	free_redirect_list()
{
	
}

void	free_ast_content(t_ast_content *content)
{
	
}

void	free_str_arr(int idx, char **arr)
{
	while (idx >= 0)
	{
		free_p(arr[idx]);
		idx--;
	}
	free(arr);
}

void	free_p(char	*p)
{
	if (p)
		free(p);
}
