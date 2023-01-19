NAME = minishell
INC = -I inc -I ~/goinfre/homebrew/opt/readline/include/readline/
CFLAGS = -Wall -Wextra -Werror $(INC)
READLINE = -lreadline -L ~/goinfre/homebrew/opt/readline/lib/

LIBFT = libft/ft_strlen.c libft/ft_strdup.c libft/ft_freearr.c libft/ft_tabsize.c\
	libft/ft_strcmp.c libft/ft_subarr.c libft/ft_strcjoin.c libft/ft_split.c \
	libft/ft_strstr.c libft/ft_tabdup.c libft/ft_substr.c libft/ft_itoa.c\

PARSE = src/parsing/parsing.c src/parsing/syntax_error.c src/parsing/lexer.c\
	src/parsing/space_skiper.c src/parsing/arr_concate.c src/parsing/str_concate.c\
	src/parsing/buffer_reset.c src/parsing/not_metachar.c src/parsing/parser.c\
	src/parsing/lst_addback.c src/parsing/last_node.c src/parsing/newnode.c\
	src/parsing/empty.c src/parsing/absolute_path.c src/parsing/expand.c\
	src/parsing/get_env_values.c src/parsing/sig_handler.c\
	src/parsing/parentheses_check.c src/parsing/init_list.c src/parsing/init_rd.c\

SRCS = src/minishell.c src/clear.c\

OBJS = $(SRCS:.c=.o) $(LIBFT:.c=.o) $(PARSE:.c=.o)

all : $(NAME)

$(NAME) : $(OBJS)
	@cc $(CFLAGS) $(OBJS) $(READLINE) -o $(NAME)
clean :
	@rm -fr $(OBJS)

fclean : clean
	@rm -fr $(NAME)

re : fclean all