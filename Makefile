# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tmarts <tmarts@student.42heilbronn.de>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/15 18:19:23 by eunskim           #+#    #+#              #
#    Updated: 2023/05/24 19:54:44 by tmarts           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 	:= minishell
CC		:= cc
CFLAGS 	:= -Wall -Wextra -Werror

WHEREIS_BREW := if test -d $(HOME)/.brew/opt/readline; then echo $(HOME)/.brew; \
				elif test -d $(HOME)/goinfre/.brew/opt/readline; then echo $(HOME)/goinfre/.brew; \
				elif test -d $(HOME)/homebrew/opt/readline; then echo $(HOME)/homebrew; \
				else echo ""; fi
				
BREW_PATH := $(shell $(WHEREIS_BREW))

READLINE_LIB := -lreadline -L $(BREW_PATH)/opt/readline/lib
READLINE_INC := -I $(BREW_PATH)/opt/readline/include/readline

SRC_DIR	= ./src/
SRCS	= $(addprefix $(SRC_DIR), \
main.c)

OBJS	:= ${SRCS:.c=.o}

all : $(NAME)

$(NAME)	: $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(READLINE_LIB)

%.o: %.c
	$(CC) $(CFLAGS) $(READLINE_INC) -c $< -o $@

clean:
	@rm -f $(OBJS) 

fclean:	clean
	@rm -f $(NAME) 
	
re: fclean all

.PHONY: all, clean, fclean, re