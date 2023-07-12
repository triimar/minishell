# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tmarts <tmarts@student.42heilbronn.de>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/08 18:19:24 by tmarts            #+#    #+#              #
#    Updated: 2023/07/12 16:25:13 by tmarts           ###   ########.fr        #
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
NAME			:= execution.a
CFLAGS 			:= -Wall -Wextra -Werror
# -g3 -fsanitize=address

LIBFT_DIR		:= ../libft
LIBFT			:= $(LIBFT_DIR)/libft.a

INCLUDE_DIR		:= ../include
HEADERS 		:= -I $(LIBFT_DIR) -I $(INCLUDE_DIR)

EXECUTION_SRCS := \
	get_envp.c \
	get_right_path.c \
	execution_utils.c \
	test_envp_and_path.c \
	child_processes.c \
	execution_errors.c \
	execution_utils.c \
	piper.c

OBJS := $(EXECUTION_SRCS:.c=.o)

#//= Make Rules =//#
all : $(NAME)

libft:
	@$(MAKE) -C $(LIBFT_DIR)

$(NAME)	: $(OBJS)
	@ar rcs $(NAME) $(OBJS) && \
	echo "$(MAGENTA)>> exec library - $(NAME) compiled <<$(RESET)"

%.o: %.c
	@$(CC) $(CFLAGS) $(HEADERS) -c $< -o $@

clean:
	@rm -f $(OBJS)
	@$(MAKE) -C $(LIBFT_DIR) clean

fclean:	clean
	@rm -f $(NAME)
	@rm -f $(LIBFT)

re: fclean all

.PHONY: all, clean, fclean, re