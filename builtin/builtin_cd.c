/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunskim <eunskim@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 17:10:48 by eunskim           #+#    #+#             */
/*   Updated: 2023/07/14 21:52:06 by eunskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int builtin_cd(t_var_list *var_list, char **cmd)
{
	chdir();
}

// int builtin_cd(char **envp, char **cmd)
// {
// 	chdir()
// }

// int main(int argc, char **argv, char **envp)
// {
	
// }
