# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: eunskim <eunskim@student.42heilbronn.de    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/15 18:19:23 by eunskim           #+#    #+#              #
#    Updated: 2023/05/15 19:07:24 by eunskim          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := minishell
CFLAGS := -Werror -Wall -Wextra

WHEREIS_BREW := if test -d $(HOME)/.brew; then echo $(HOME)/.brew; \
				elif test -d $(HOME)/goinfre/.brew; then echo $(HOME)/goinfre/.brew; \
				else echo ""; fi

BREW_PATH := $(shell $(WHEREIS_BREW))

READLINE_LIB := -lreadline -L $(BREW_PATH)/opt/readline/lib
READLINE_INC := -I $(BREW_PATH)/opt/readline/include

all : $(NAME)

$(NAME)	: $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(READLINE_LIB)

%.o: %.c
	$(CC) $(CFLAGS) $(READLINE_INC) -c $< -o $@
