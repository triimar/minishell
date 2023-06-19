# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: eunskim <eunskim@student.42heilbronn.de    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/19 14:32:56 by eunskim           #+#    #+#              #
#    Updated: 2023/06/19 18:30:15 by eunskim          ###   ########.fr        #
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
NAME			:= parser
CFLAGS 			:= -Wall -Wextra -Werror -g3 -fsanitize=address

LIBFT_DIR		:= ../libft
LIBFT			:= $(LIBFT_DIR)/libft.a

INCLUDE_DIR		:= ../include
HEADERS 		:= -I $(LIBFT_DIR) -I $(INCLUDE_DIR)

LEXER_DIR		:= ../lexer
LEXER			:= $(LEXER_DIR)/lexer.a

PARSER_SRCS := \
	parser.c \
	parser_2.c \
	parser_utils.c \
	parser_linked_list_utils.c \
	token_scanner_utils.c \
	cmd_node_utils.c \
	ast_utils.c \
	parser_free.c
	# parser_test.c

OBJS := $(PARSER_SRCS:.c=.o)

#//= Make Rules =//#
all : $(NAME)

$(LEXER):
	@$(MAKE) -C $(LEXER_DIR)

$(NAME)	: $(LEXER) $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LIBFT) $(LEXER) && \
	echo "$(BLUE)>> Unit testing - parser <<$(RESET)" && \
	echo "$(GREEN)Compilation successful!$(RESET)"

%.o: %.c
	@$(CC) $(CFLAGS) $(HEADERS) -c $< -o $@

clean:
	@rm -f $(OBJS)
	@$(MAKE) -C $(LEXER_DIR) clean

fclean:	clean
	@rm -f $(NAME)
	@rm -f $(LEXER)
	@rm -f $(LIBFT)

re: fclean all

.PHONY: all, clean, fclean, re, lexer