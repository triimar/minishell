/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunskim <eunskim@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 11:19:40 by eunskim           #+#    #+#             */
/*   Updated: 2023/07/12 19:01:01 by eunskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

# include <stdbool.h>
# include <stdlib.h>
# include <stdio.h>
# include "minishell.h"
# include "parser.h"

typedef struct s_var_list	t_var_list;

typedef enum e_expander_exit_code
{
	EXPANDER_SUCCESS,
	EXPANDER_FAILURE
}	t_expander_exit_code;

/* expander.c */
t_expander_exit_code	expander_executor(t_ast *ast_root, t_var_list *var_head);
char					*expander(char *to_expand, t_var_list *var_head, bool *malloc_failed);
char					*double_quote_expansion(char *str, int *i, t_var_list *var_head, bool *malloc_failed);
char					*substring_expansion(char *str, t_var_list *var_head, bool *malloc_failed);
char					*variable_expansion(char *str, int *i, t_var_list *var_head, bool *malloc_failed);

/* expander_utils.c */
char					*get_value_for_key(t_var_list *var_head, const char *key);
int						ft_strcmp(const char *s1, const char *s2);
char					*ft_strdup_pt(const char *start, char *delimiter);

/* expander_here_end.c */
char					*quote_removal_here_end(char *here_end, bool *malloc_failed);
char					*quote_removal(char *str, int *i, bool *malloc_failed);

/* expander_executor_utils.c */
void					execute_expander_on_tree(t_ast *node, t_var_list *var_head, bool *malloc_failed);
void					execute_expander_on_content(t_ast_content *content, t_var_list *var_head, bool *malloc_failed);
void					execute_expander_on_redirect_list(t_redirect *redirect, t_var_list *var_head, bool *malloc_failed);
void					execute_expander_on_assignments(t_assignment *assignments, t_var_list *var_head, bool *malloc_failed);
void					execute_expander_on_cmd_array(char **cmd, t_var_list *var_head, bool *malloc_failed);

#endif