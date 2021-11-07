# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cwhis <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/07/05 18:22:40 by xzulema           #+#    #+#              #
#    Updated: 2021/09/20 20:45:54 by cwhis            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC=gcc
SCHOOL=$(HOME)/.brew
HOMEE=usr/local
CFLAGS=-Wall -Werror -Werror
FLAGS=-ltermcap -lreadline -L/$(SCHOOL)/Cellar/readline/8.1/lib -I/$(SCHOOL)/Cellar/readline/8.1/include
NAME=minishell
SRCS=	minishell.c exec.c env.c utils.c list_utils.c errors.c path.c exec_utils.c exec_new_utils.c signals_utils.c exec_norm_utils.c\
		parser/special_split.c parser/parser_utils.c parser/parse_input.c parser/input.c parser/parse_vars.c\
		builtins/ft_cd.c builtins/ft_env.c builtins/ft_export.c builtins/start_builtin.c\
		builtins/ft_pwd.c builtins/ft_unset.c builtins/ft_echo.c builtins/ft_exit.c
OBJS=$(SRCS:.c=.o)
HEADER=minishell.h
LIBFT=libft/libft.a

all: $(NAME)

$(NAME): $(OBJS) $(SRCS) Makefile $(HEADER) $(LIBFT)
	$(CC) $(CFLAGS) $(FLAGS) $(OBJS) $(LIBFT) -o $(NAME)
$(LIBFT):
	cd libft && make && make bonus
%.o: %.c
	$(CC) $(CFLAGS) -c $^ -o $@
clean: 
	rm -f $(OBJS)
	cd libft && make clean
fclean: clean
	rm -f $(NAME)
	cd libft && make fclean
re: fclean all

.PHONY: all clean fclean re
