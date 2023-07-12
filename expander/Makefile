# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: eunskim <eunskim@student.42heilbronn.de    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/23 17:23:14 by eunskim           #+#    #+#              #
#    Updated: 2023/07/12 17:10:38 by eunskim          ###   ########.fr        #
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
NAME			:= expander
CFLAGS 			:= -Wall -Wextra -Werror
# -g3 -fsanitize=address

LIBFT_DIR		:= ../libft
LIBFT			:= $(LIBFT_DIR)/libft.a

INCLUDE_DIR		:= ../include
HEADERS 		:= -I $(LIBFT_DIR) -I $(INCLUDE_DIR)

EXPANDER_SRCS := \
	expander.c \
	expander_utils.c \
	expander_here_end.c \
	expander_executor_utils.c

OBJS := $(EXPANDER_SRCS:.c=.o)

#//= Make Rules =//#
all : libft $(NAME)

libft:
	@$(MAKE) -C $(LIBFT_DIR)

$(NAME)	: $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LIBFT) && \
	echo "$(CYAN)>> Unit testing - expander <<$(RESET)" && \
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