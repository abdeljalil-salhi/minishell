# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: absalhi <absalhi@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/26 22:31:07 by absalhi           #+#    #+#              #
#    Updated: 2023/02/05 06:58:01 by absalhi          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	minishell

CC			=	cc
RM			=	rm -rf
INC			=	-I inc -I ~/goinfre/homebrew/opt/readline/include/readline/
CFLAGS		=	-Wall -Wextra -Werror $(INC)
READLINE	=	-lreadline -L ~/goinfre/homebrew/opt/readline/lib/

NONE		=	'\033[0m'
GREEN		=	'\033[32m'
GRAY		=	'\033[2;37m'
ITALIC		=	'\033[3m'

_DBUILTINS	=	builtins
_BUILTINS	=	builtins_utils.c re_cd.c re_echo.c re_env.c			\
				re_exit.c re_export.c re_pwd.c re_unset.c
BUILTINS	=	$(addprefix $(_DBUILTINS)/, $(_BUILTINS))

_DLIBFT		=	libft
_LIBFT		=	ft_strlen.c ft_strdup.c ft_freearr.c ft_tabsize.c	\
				ft_strcmp.c ft_subarr.c ft_strcjoin.c ft_split.c	\
				ft_strstr.c ft_tabdup.c ft_substr.c ft_itoa.c		\
				ft_strchr.c ft_strjoin.c ft_atoi.c ft_bzero.c		\
				ft_strrchr.c ft_dprintf.c ft_getenv.c
LIBFT		=	$(addprefix $(_DLIBFT)/, $(_LIBFT))

_DPARSE		=	src/parsing
_PARSE		=	parsing.c syntax_error.c lexer.c					\
				concate.c parser.c lst_addback.c					\
				newnode.c absolute_path.c expand.c					\
				parentheses_check.c init_list.c init_rd.c			\
				wildcard.c readdir.c pattern_match.c
PARSE		=	$(addprefix $(_DPARSE)/, $(_PARSE))

_DEXEC		=	src/execution
_EXEC		=	supervisor.c exec_command.c exec_builtin.c			\
				exec_heredoc.c init_session.c supervisor_utils.c	\
				exec_helpers.c
EXEC		=	$(addprefix $(_DEXEC)/, $(_EXEC))

_DDEBUG		=	src/debug
_DEBUG		=	print_struct.c
DEBUG		=	$(addprefix $(_DDEBUG)/, $(_DEBUG))

_DSRCS		=	src
_SRCS		=	minishell.c clear.c prompt.c
SRCS		=	$(addprefix $(_DSRCS)/, $(_SRCS))

OBJS		=	$(SRCS:.c=.o) $(LIBFT:.c=.o) $(PARSE:.c=.o)			\
				$(EXEC:.c=.o) $(BUILTINS:.c=.o) $(DEBUG:.c=.o)

.c.o		:
				@echo $(ITALIC)$(GRAY) "     - Making $<..." $(NONE)
				@$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)

all			:	$(NAME)

get_brew	:
				@echo $(ITALIC)$(GRAY) "     - Installing Homebrew..." $(NONE)
				@cd ~/goinfre/ && \
				if [ -d homebrew ]; then \
					echo $(GREEN)"- Homebrew already installed -"$(NONE); \
					exit 0; \
				fi
				@cd ~/goinfre/ && mkdir homebrew && curl -L https://github.com/Homebrew/brew/tarball/master | tar xz --strip 1 -C homebrew
				@cd ~/goinfre/ && eval "$$(homebrew/bin/brew shellenv)"
				@brew update --force --quiet
				@chmod -R go-w "$$(brew --prefix)/share/zsh"

get_readline:
				@echo $(ITALIC)$(GRAY) "     - Installing readline..." $(NONE)
				@brew install -q readline

install		:	get_brew get_readline

$(NAME)		:	$(OBJS)
				@echo $(ITALIC)$(GRAY) "     - Compiling $(NAME)..." $(NONE)
				@stty -echoctl
				@$(CC) $(CFLAGS) $(OBJS) $(READLINE) -o $(NAME)
				@echo $(GREEN)"- Compiled -"$(NONE)

debug		:	CFLAGS += -D DEBUG
debug		:	fclean all

clean		:
				@echo $(ITALIC)$(GRAY) "     - Removing object files..." $(NONE)
				@$(RM) $(OBJS)

fclean		:	clean
				@echo $(ITALIC)$(GRAY) "     - Removing $(NAME)..." $(NONE)
				@$(RM) $(NAME)

re			:	fclean all

norm		:
				@echo $(NONE)$(ITALIC)$(GREEN) "     ~ Checking header files norminette..." $(GRAY)
				@norminette inc/*.h
				@echo $(NONE)$(ITALIC)$(GREEN) "     ~ Checking source files norminette..." $(GRAY)
				@norminette $(_DPARSE)/*.c
				@norminette $(_DEXEC)/*.c
				@norminette $(_DDEBUG)/*.c
				@norminette $(_DSRCS)/*.c
				@echo $(NONE)$(ITALIC)$(GREEN) "     ~ Checking libft norminette..." $(GRAY)
				@norminette $(_DLIBFT)/*.c
				@echo $(NONE)$(ITALIC)$(GREEN) "     ~ Checking builtins norminette..." $(GRAY)
				@norminette $(_DBUILTINS)/*.c

.PHONY		:	all get_brew get_readline install debug clean fclean re norm
