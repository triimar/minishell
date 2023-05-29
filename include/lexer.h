/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunskim <eunskim@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 19:08:02 by eunskim           #+#    #+#             */
/*   Updated: 2023/05/29 16:02:02 by eunskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
#define LEXER_H

# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>

# define REDIRECTIONS "><"
# define WHITESPACES "\t\v\f\r "
# define QUOTES "\"\'"

typedef enum e_lexer_exit_code
{
	LEXER_SUCCESS,
	MALLOC_ERROR,
	UNCLOSED_QUOTE
}	t_lexer_exit_code;

typedef enum e_token_type
{
	TOKEN_EOF,
	TOKEN_WORD,
	TOKEN_ASSIGNMENT_WORD,
	TOKEN_GREAT,
	TOKEN_DGREAT,
	TOKEN_LESS,
	TOKEN_DLESS,
	TOKEN_PIPE,
	TOKEN_ERROR
}	t_token_type;

typedef struct s_scanner
{
	const char	*start;
	const char	*current;
}	t_scanner;

typedef struct s_token
{
	t_token_type	type;
	const char		*start;
	int				length;
}	t_token;

typedef struct s_token_list
{
	t_token			*token;
	t_token_list	*next;
}	t_token_list;

typedef struct s_lexer
{
	t_token_list	*head;
	t_token_list	*tail;
	int				unclosed_quote_error_flag;
}	t_lexer;

#endif LEXER_H