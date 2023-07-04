/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunskim <eunskim@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 11:19:40 by eunskim           #+#    #+#             */
/*   Updated: 2023/07/04 21:09:49 by eunskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

# include <stdbool.h>
# include <stdlib.h>
# include <stdio.h>
# include "minishell.h"
# include "parser.h"

typedef enum e_expander_exit_code
{
	EXPANDER_SUCCESS,
	EXPANDER_FAILURE
}	t_expander_exit_code;

#endif