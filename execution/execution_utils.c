/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarts <tmarts@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 18:07:15 by tmarts            #+#    #+#             */
/*   Updated: 2023/07/09 18:07:32 by tmarts           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	ft_free_ptpt(char **array, int str_count)
{
	str_count--;
	while (str_count >= 0)
	{
		free(array[str_count]);
		str_count--;
	}
	free (array);
	return ;
}