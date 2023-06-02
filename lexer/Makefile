# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: eunskim <eunskim@student.42heilbronn.de    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/30 14:11:52 by eunskim           #+#    #+#              #
#    Updated: 2023/06/02 16:28:14 by eunskim          ###   ########.fr        #
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
NAME			:= lexer
CFLAGS 			:= -Wall -Wextra -Werror -g3 -fsanitize=address

LIBFT_DIR		:= ../libft
INCLUDE_DIR		:= ../include

HEADERS 		:= -I $(LIBFT_DIR) -I $(INCLUDE_DIR)
LIBFT			:= $(LIBFT_DIR)/libft.a

LEXER_SRCS := \
	for_test.c \
	lexer_utils.c \
	lexer.c \
	scanner_utils.c \
	token_list_utils.c

OBJS := $(LEXER_SRCS:.c=.o)

#//= Make Rules =//#
all : libft $(NAME)

libft:
	@$(MAKE) -C $(LIBFT_DIR)

$(NAME)	: $(OBJS)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT) && \
	echo "$(MAGENTA)>> Unit testing - lexer <<$(RESET)" && \
	echo "$(GREEN)Compilation successful!$(RESET)"

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