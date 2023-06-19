# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: eunskim <eunskim@student.42heilbronn.de    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/30 14:11:52 by eunskim           #+#    #+#              #
#    Updated: 2023/06/19 16:44:21 by eunskim          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#//= Colors =//#
BOLD	:= \033[1m
BLACK	:= \033[30;1m
RED		:= \033[31;1m
GREEN	:= \033[32;1m
YELLOW	:= \033[33;1m
BLUE	:= \033[34;1m
MAGENTA	:= \033[35;1m
CYAN	:= \033[36;1m
WHITE	:= \033[37;1m
RESET	:= \033[0m

#//= Mandatory part =//#
NAME			:= lexer.a
CFLAGS 			:= -Wall -Wextra -Werror

LIBFT_DIR		:= ../libft
LIBFT			:= $(LIBFT_DIR)/libft.a

INCLUDE_DIR		:= ../include
HEADERS 		:= -I $(LIBFT_DIR) -I $(INCLUDE_DIR)

LEXER_SRCS := \
	lexer.c \
	lexer_utils.c \
	scanner_utils.c \
	token_list_utils.c \
	for_test.c

OBJS := $(LEXER_SRCS:.c=.o)

#//= Make Rules =//#
all : libft $(NAME)

libft:
	@$(MAKE) -C $(LIBFT_DIR)

$(NAME)	: $(OBJS)
	@ar rcs $(NAME) $(OBJS) && \
	echo "$(YELLOW)>> library - $(NAME) compiled <<$(RESET)"

%.o: %.c
	@$(CC) $(CFLAGS) $(HEADERS) -c $< -o $@

clean:
	@rm -f $(OBJS)
	@$(MAKE) -C $(LIBFT_DIR) clean

fclean:	clean
	@rm -f $(NAME)
	@rm -f $(LIBFT)
	
re: fclean all

.PHONY: all, clean, fclean, re, libft