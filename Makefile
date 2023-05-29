# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tmarts <tmarts@student.42heilbronn.de>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/15 18:19:23 by eunskim           #+#    #+#              #
#    Updated: 2023/05/29 15:24:43 by tmarts           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 	:= minishell
CC		:= cc
CFLAGS 	:= -Wall -Wextra -Werror

WHEREIS_BREW := if test -d $(HOME)/.brew/opt/readline; then echo $(HOME)/.brew; \
				elif test -d $(HOME)/goinfre/.brew/opt/readline; then echo $(HOME)/goinfre/.brew; \
				elif test -d $(HOME)/homebrew/opt/readline; then echo $(HOME)/homebrew; \
				else echo ""; fi
				
BREW_PATH	:= $(shell $(WHEREIS_BREW))
LIBFT		:= ./libft
HEADERS 	:= -I $(BREW_PATH)/opt/readline/include -I $(LIBFT)
LIBS		:= -lreadline -L $(BREW_PATH)/opt/readline/lib $(LIBFT)/libft.a

SRC_DIR	:= ./src/
SRCS	:= $(addprefix $(SRC_DIR), \
main.c \
builtin_exit.c)

OBJS	:= ${SRCS:.c=.o}

all : libft $(NAME)

libft:
	@$(MAKE) -C $(LIBFT)

$(NAME)	: $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBS)

%.o: %.c
	$(CC) $(CFLAGS) $(HEADERS) -c $< -o $@ 

clean:
	@rm -f $(OBJS) 
	@$(MAKE) -C $(LIBFT) fclean

fclean:	clean
	@rm -f $(NAME) 
	
re: fclean all

.PHONY: all, clean, fclean, re, libft