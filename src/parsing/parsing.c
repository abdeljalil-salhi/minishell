/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: absalhi <absalhi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 11:50:45 by mtellami          #+#    #+#             */
/*   Updated: 2023/02/05 00:46:14 by absalhi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	not_metachar(char c)
{
	if (c != RIGHT_ARROW && c != LEFT_ARROW
		&& c != PIPE && c != SPACE && c != TAB
		&& c != AMPERSAND && c != OPEN_PARENTHESE
		&& c != CLOSE_PARENTHESE)
		return (1);
	return (0);
}

void	space_skiper(char *str, int *i)
{
	while (str[*i] == SPACE || str[*i] == TAB)
		(*i)++;
}

int	empty(char *input)
{
	int	i;

	i = -1;
	if (!input)
	{
		printf("exit\n");
		exit(g_data.exit_status);
	}
	while (input[++i])
		if (input[i] != SPACE && input[i] != TAB)
			return (0);
	free(input);
	return (1);
}

void	sig_handler(int sig)
{
	if (sig == SIGINT && !g_data.here_doc)
	{
		printf("\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	parsing(char *input)
{
	char	**ps;

	g_data.errors = 0;
	ps = lexer(input);
	if (syntax_error(ps))
	{
		g_data.errors = 1;
		free(input);
		ft_freearr(ps);
		return ;
	}
	parser(ps);
	ft_freearr(ps);
	free(input);
}
