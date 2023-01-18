/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellami <mtellami@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 11:13:58 by mtellami          #+#    #+#             */
/*   Updated: 2023/01/18 18:38:01 by mtellami         ###   ########.fr       */
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

# define GREEN "\e[01;32m"
# define RESET "\e[00m"
# define RED "\e[00;31m"

int g_exit_status;

enum e_token
{
	RIGHT_ARROW = '>',
	LEFT_ARROW = '<',
	PIPE = '|',
	DOLLAR_SIGH = '$',
	SINGLE_QUOTE = '\'',
	DOUBLE_QUOTE = '"',
	SPACE = ' ',
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

typedef struct s_redir
{
	int				type;//done
	int				fd;//done	
	char			*file;//done;
	struct s_redir *next;//done
	struct s_redir *previous;//done
}	t_redir;

typedef struct s_proc
{
	char 			*cmd;//done
	char 			**args; // done
	int  			separator;//done
	int				level;// done
	struct s_redir	*head;// done
	struct s_proc	*next;// done
	struct s_proc	*previous;// done
}	t_proc;

typedef struct s_data
{
	char 			**env;// done
	int				errors;// done
	struct s_proc	*head;// done
}	t_data;

void	rl_replace_line(const char *str, int i);

int		ft_tabsize(char **tab);
char	*ft_strdup(char *str);
int		ft_strlen(char *str);
void	ft_freearr(char **tab);
int		ft_strcmp(char *s1, char *s2);
char	*ft_strcjoin(char *s1, char c, char *s2);
char	**ft_split(char const *s, char c);
char	*ft_strstr(char *str, char *to_find);
char	**ft_tabdup(char **tab);
char	*ft_substr(char *s, unsigned int start, size_t len);
char	*ft_itoa(int n);

void	parsing(char *input, t_data *data);
int		syntax_error(char **lx);
char	**lexer(char *input);
int		empty(char *input);
void	space_skiper(char *str, int *i);
char	**arr_concate(char **tab, char *str);
char	*str_concate(char *s, char c);
int		not_metachar(char c);
void	buffer_reset(char **buffer);
void	parser(char **lx, t_data *data);
t_proc	*pc_new_node(char **args, int sep, int lvl);
void	pc_addback(t_proc **lst, t_proc *new);
t_proc	*pc_last_node(t_proc *lst);
char	**ft_subarr(char **tab, int start, int size);
void	rd_addback(t_redir **head, t_redir *new);
t_redir	*rd_last_node(t_redir *lst);
t_redir	*rd_new_node(char *file, int type);
void	clear(t_data *data);
char	*absolute_path(char *cmd, char **env);
char	*expand(char *str, char **env);
char	*get_env_values(char *str, char **env);
void	sig_handler(int sig);


#endif