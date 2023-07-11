/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_data_init.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarts <tmarts@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 17:19:17 by tmarts            #+#    #+#             */
/*   Updated: 2023/07/11 15:07:35 by tmarts           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include<stdio.h>
// #include<stdlib.h>
// #include<stddef.h>

#include "minishell.h"

t_ms_exit_code	initiate_var_list(t_var_list **var_list)
{
	t_var_list	*new_var_node;
	char		*delimiter_pt;
	int			i;

	i = 0;
	while (environ[i] != NULL)
	{
		new_var_node = (t_var_list *)ft_calloc(1, sizeof(t_var_list));
		if (!new_var_node)
			return (free_var_list(*var_list), MS_MALLOC_ERROR);
		if (i % 2 == 0) //to test envp maker for execve
			new_var_node->env_flag = 1;
		delimiter_pt = ft_strchr(environ[i], '=');
		new_var_node->key = ft_strdup_pt(environ[i], (delimiter_pt));
		if (!new_var_node->key)
			return (free_var_list(*var_list), MS_MALLOC_ERROR);
		new_var_node->value = ft_strdup(delimiter_pt + 1);
		if (!new_var_node->value)
			return (free_var_list(*var_list), MS_MALLOC_ERROR);
		ft_lstadd_back_ms(var_list, new_var_node);
		i++;
	}
	return (MINISHELL_SUCCESS);
}

void	free_var_list(t_var_list *var_list)
{
	t_var_list	*free_this;

	while (var_list != NULL)
	{
		if (var_list->key)
			free (var_list->key);
		if (var_list->value)
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
		printf("\n[%s]\n", printer->key);
		printf("[%s]\n", printer->value);
		printf("ENV_FLAG[%d]\n", printer->env_flag);
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