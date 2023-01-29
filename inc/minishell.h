/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellami <mtellami@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 11:13:58 by mtellami          #+#    #+#             */
/*   Updated: 2023/01/29 22:41:54 by mtellami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <errno.h>

# define GREEN "\e[01;32m"
# define RESET "\e[00m"
# define RED "\e[00;31m"
# define NAME "minishell-3.2$ "
# define HERE_DOC "/tmp/.heredoc"

# ifndef DEBUG
#  define DEBUG 0
# endif

enum e_token
{
	RIGHT_ARROW = '>',
	LEFT_ARROW = '<',
	PIPE = '|',
	DOLLAR_SIGH = '$',
	SINGLE_QUOTE = '\'',
	DOUBLE_QUOTE = '"',
	SPACE = ' ',
	TAB = '\t',
	QUESTION_MARK = '?',
	AMPERSAND = '&',
	OPEN_PARENTHESE = '(',
	CLOSE_PARENTHESE = ')',
	ASTERISK = '*',
};

enum e_redirections
{
	INPUT,
	OUTPUT,
	HEREDOC,
	APPEND,
};

enum e_separator
{
	LAST_CMD,
	AND_TOKEN,
	OR_TOKEN,
	PIPE_TOKEN,
};

/*
	<-- man parsing -->
	- redirection struct :
	 + type : type of next separator (check separators enum ^)
	 + fd : file descriptor in success, -1 if permission denied -2 if no such file,
	 		-3 if here_doc
	 + file : file path, delimiter in here_doc

	- process struct :
	 + cmd : command absolute path, NULL if command not found, empty str if no command (< filein > fileout)
	 + args : argument array, NULL if no args
	 + separator : check types in enum ^
	 + head : header of redirections list, NULL if no redirections

	- main struct (data)
	 + env : environment array, main shell env
	 + errors : used in parsing if syntax error detected
	 + head : the header of process list
*/

typedef struct s_redir
{
	int				type;
	int				fd;
	char			*file;
	struct s_redir	*next;
	struct s_redir	*previous;
}	t_redir;

typedef struct s_proc
{
	char			*cmd;
	char			**args;
	int				separator;
	int				level;
	struct s_redir	*head;
	struct s_proc	*next;
	struct s_proc	*previous;
}	t_proc;

typedef struct s_builtins
{
	char	*name;
	void	(*func)(char **);
}	t_builtins;

typedef struct s_data
{
	char			**env;
	int				errors;
	int				exit_status;
	t_builtins		builtins[7];
	struct s_proc	*head;
}	t_data;

t_data	g_data;

void	rl_replace_line(const char *str, int i);

/* ------------- libft ------------- */
int		ft_tabsize(char **tab);
int		ft_atoi(const char *str);
char	*ft_strdup(char *str);
void	*ft_memset(void *b, int c, size_t len);
void	ft_bzero(void *s, size_t n);
int		ft_strlen(char *str);
void	ft_freearr(char **tab);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_strcmp(char *s1, char *s2);
char	*ft_strcjoin(char *s1, char c, char *s2);
char	**ft_split(char const *s, char c);
char	*ft_strstr(char *str, char *to_find);
char	**ft_tabdup(char **tab);
char	*ft_substr(char *s, unsigned int start, size_t len);
char	*ft_itoa(int n);
char	*ft_strchr(char *str, int c);
char	*ft_strjoin(char *s1, char *s2);

/* ------------- parsing ------------- */
void	parsing(char *input);
int		syntax_error(char **lx);
char	**lexer(char *input);
int		empty(char *input);
void	space_skiper(char *str, int *i);
char	**arr_concate(char **tab, char *str);
char	*str_concate(char *s, char c);
int		not_metachar(char c);
void	buffer_reset(char **buffer);
void	parser(char **lx);
t_proc	*pc_new_node(char **args, int sep, int lvl);
void	pc_addback(t_proc **lst, t_proc *new);
t_proc	*pc_last_node(t_proc *lst);
char	**ft_subarr(char **tab, int start, int size);
void	rd_addback(t_redir **head, t_redir *new);
t_redir	*rd_last_node(t_redir *lst);
t_redir	*rd_new_node(char *file, int type);
void	clear(void);
char	*absolute_path(char *cmd);
char	*expand(char *str);
void	sig_handler(int sig);
int		parentheses_check(char **lx, int i, int *x, int *y);
void	init_list(char **lx);
void	init_rd(void);
int		get_separator(char **lx, int i);
char	*del_quote(char *str);

/* ------------- builtins ------------- */
void	init_builtins(void);
int		check_home(void);
void	cd_home(void);
int		check_var(char *str);
void	value_inquotes(int i);
char	*home_path(void);
void	sort_env(void);
void	set_pwd(void);
int		valid_ident(char *str);
void	set_oldpwd();
void	re_cd(char **args);
void	re_echo(char **args);
void	re_env(char **args);
void	re_exit(char **args);
void	re_export(char **args);
void	re_pwd(char **args);
void	re_unset(char **args);

/* ------------- execution ------------- */
void	supervisor(void);
int		executor(t_proc *proc, int level, int _pipe[2], int prev_pipe[2]);
int		exit_status(int status);
int		is_builtin(char *cmd);
int		exec_builtin(char *cmd, char **args);
void	exec_heredoc(t_redir *current);

/* ------------- debugging ------------- */
void	printf_struct(void);

#endif