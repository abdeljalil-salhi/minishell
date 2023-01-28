# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: absalhi <absalhi@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/26 22:31:07 by absalhi           #+#    #+#              #
#    Updated: 2023/01/28 14:14:28 by absalhi          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
INC = -I inc -I ~/goinfre/homebrew/opt/readline/include/readline/
CFLAGS = -Wall -Wextra -Werror $(INC) -fsanitize=address -g3
READLINE = -lreadline -L ~/goinfre/homebrew/opt/readline/lib/

LIBFT = libft/ft_strlen.c libft/ft_strdup.c libft/ft_freearr.c libft/ft_tabsize.c\
	libft/ft_strcmp.c libft/ft_subarr.c libft/ft_strcjoin.c libft/ft_split.c \
	libft/ft_strstr.c libft/ft_tabdup.c libft/ft_substr.c libft/ft_itoa.c\
	libft/ft_strchr.c libft/ft_strjoin.c libft/ft_atoi.c libft/ft_bzero.c

PARSE = src/parsing/parsing.c src/parsing/syntax_error.c src/parsing/lexer.c\
	src/parsing/space_skiper.c src/parsing/arr_concate.c src/parsing/str_concate.c\
	src/parsing/buffer_reset.c src/parsing/not_metachar.c src/parsing/parser.c\
	src/parsing/lst_addback.c src/parsing/last_node.c src/parsing/newnode.c\
	src/parsing/empty.c src/parsing/absolute_path.c src/parsing/expand.c\
	src/parsing/sig_handler.c src/parsing/parentheses_check.c\
	src/parsing/init_list.c src/parsing/init_rd.c

_BUILTINS = builtins_utils.c re_cd.c re_echo.c re_env.c re_exit.c re_export.c\
	re_pwd.c re_unset.c
BUILTINS = $(addprefix builtins/, $(_BUILTINS))

_EXEC = supervisor.c exec_command.c exec_builtin.c
EXEC = $(addprefix src/execution/, $(_EXEC))

_DEBUG = print_struct.c
DEBUG = $(addprefix src/debug/, $(_DEBUG))

SRCS = src/minishell.c src/clear.c

OBJS = $(SRCS:.c=.o) $(LIBFT:.c=.o) $(PARSE:.c=.o) $(EXEC:.c=.o)\
	$(BUILTINS:.c=.o) $(DEBUG:.c=.o)

.c.o :
	@cc $(CFLAGS) -c $< -o $(<:.c=.o)

all : header $(NAME)

header :
	@echo "Compiling $(NAME)..."

$(NAME) : $(OBJS)
	@cc $(CFLAGS) $(OBJS) $(READLINE) -o $(NAME)

debug : CFLAGS += -D DEBUG
debug : fclean all

clean :
	@rm -fr $(OBJS)

fclean : clean
	@rm -fr $(NAME)

re : fclean all