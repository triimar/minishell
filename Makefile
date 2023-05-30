# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: eunskim <eunskim@student.42heilbronn.de    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/15 18:19:23 by eunskim           #+#    #+#              #
#    Updated: 2023/05/30 13:07:44 by eunskim          ###   ########.fr        #
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
NAME			:= minishell
# CC				:= cc # ($(CC) is by default cc in makefile)
CFLAGS 			:= -Wall -Wextra -Werror
# -g3 -fsanitze=address # added sanitizer flag for testing

WHEREIS_BREW	:= if test -d $(HOME)/.brew/opt/readline; then echo $(HOME)/.brew; \
					elif test -d $(HOME)/goinfre/.brew/opt/readline; then echo $(HOME)/goinfre/.brew; \
					elif test -d $(HOME)/homebrew/opt/readline; then echo $(HOME)/homebrew; \
					else echo ""; fi		
BREW_PATH		:= $(shell $(WHEREIS_BREW))
LIBFT_DIR		:= ./libft
INCLUDE_DIR		:= ./include

HEADERS 		:= -I $(BREW_PATH)/opt/readline/include -I $(LIBFT_DIR) -I $(INCLUDE_DIR)
LIBFT			:= $(LIBFT_DIR)/libft.a
LIBS			:= -lreadline -L $(BREW_PATH)/opt/readline/lib $(LIBFT)

SRCS	:= \
	src/main.c \
	src/builtin_exit.c

# LEXER_SRC := \
# 	lexer/for_test.c \
# 	lexer/lexer_utils.c \
# 	lexer/lexer.c \
# 	lexer/scanner_utils.c \
# 	lexer/token_list_utils.c

OBJS := $(SRCS:.c=.o)
# $(LEXER_SRC:.c=.o)

#//= Make Rules =//#
all : libft $(NAME)

libft:
	@$(MAKE) -C $(LIBFT_DIR)

$(NAME)	: $(OBJS)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBS) && \
	echo "$(MAGENTA)>> Mandatory part - Minishell $(RESET)" && \
	echo "$(GREEN)Compilation successful!$(RESET)"

%.o: %.c
	@$(CC) $(CFLAGS) $(HEADERS) -c $< -o $@

clean:
	@rm -f $(OBJS)
	@$(MAKE) -C $(LIBFT_DIR) clean
# fclean to clean for libft

fclean:	clean
	@rm -f $(NAME)
	@rm -f $(LIBFT)
	
re: fclean all

.PHONY: all, clean, fclean, re, libft