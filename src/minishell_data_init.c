/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_data_init.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarts <tmarts@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 17:19:17 by tmarts            #+#    #+#             */
/*   Updated: 2023/07/05 00:07:02 by tmarts           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include<stdio.h>
// #include<stdlib.h>
// #include<stddef.h>

#include "minishell.h"

int	initiate_var_list(t_var_list **var_list)
{
	t_var_list	*new_var_node;
	char		*delimiter_pt;
	int			i;

	i = 0;
	while (environ[i] != NULL)
	{
		new_var_node = (t_var_list *)ft_calloc(1, sizeof(t_var_list));
		if (!new_var_node)
			return (5); //malloc fail!! how to proceed?
		new_var_node->env_flag = 1;
		delimiter_pt = ft_strchr(environ[i], '=');
		new_var_node->key = ft_strdup_pt(environ[i], (delimiter_pt + 1)); // if key==0 is it malloc fail?
		new_var_node->value = ft_strdup(delimiter_pt + 1);
		ft_lstadd_back_mini(var_list, new_var_node);
		i++;
	}
	return (0);
}

void	free_var_list(t_var_list *var_list)
{
	t_var_list	*free_this;
	
	while (var_list != NULL)
	{
		free (var_list->key);
		free (var_list->value);
		free_this = var_list;
		var_list = var_list->next;
		free (free_this);
	}
}

void	print_var_list(t_var_list *var_list)
{
	t_var_list	*printer;
	
	printer = var_list;
	printf("\n------------ VAR_LIST -----------\n\n");
	while (printer != NULL)
	{
		printf("\n[%s]\n[%s]\nENV_FLAG[%d]\n", printer->key, printer->value, printer->env_flag);
		printer = printer->next;
	}
	printf("\n----------------------------------\n");
}
// int	main(void)
// {
// 	t_var_list	*var_list;
// 	t_var_list	*printer;
// 	t_var_list	*free_this;
// 	int			i;

// 	i = 0;
// 	var_list = NULL;
// 	initiate_var_list(&var_list);
// 	printer = var_list;
// 	while (printer != NULL)
// 	{
// 		printf("[%d] [%s] [%s] [%d]\n", i, printer->key, printer->value, printer->env_flag);
// 		printer = printer->next;
// 		i++;
// 	}

// 	while(var_list != NULL)
// 	{
// 		free (var_list->key);
// 		free (var_list->value);
// 		free_this = var_list;
// 		var_list = var_list->next;
// 		free (free_this);
// 	}

// 	system("leaks a.out");
// 	return(0);
// }