NAME = minishell
INC = -I inc -I ~/goinfre/homebrew/opt/readline/include/readline/
CFLAGS = -Wall -Wextra -Werror $(INC)
READLINE = -lreadline -L ~/goinfre/homebrew/opt/readline/lib/

LIBFT = libft/ft_strlen.c libft/ft_strdup.c libft/ft_freearr.c libft/ft_tabsize.c\
	libft/ft_strcmp.c libft/ft_subarr.c libft/ft_strcjoin.c libft/ft_split.c \
	libft/ft_strstr.c libft/ft_tabdup.c libft/ft_substr.c libft/ft_itoa.c\

SRCS = src/minishell.c src/parsing.c src/syntax_error.c src/empty.c src/lexer.c\
	src/space_skiper.c src/arr_concate.c src/str_concate.c src/buffer_reset.c\
	src/not_metachar.c src/parser.c linked_list/lst_addback.c linked_list/last_node.c linked_list/newnode.c src/clear.c src/absolute_path.c src/expand.c src/get_env_values.c src/sig_handler.c\

OBJS = $(SRCS:.c=.o) $(LIBFT:.c=.o)

all : $(NAME)

$(NAME) : $(OBJS)
	@cc $(CFLAGS) $(OBJS) $(READLINE) -o $(NAME)
clean :
	@rm -fr $(OBJS)

fclean : clean
	@rm -fr $(NAME)

re : fclean all