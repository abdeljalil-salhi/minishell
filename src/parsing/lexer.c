/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellami <mtellami@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 11:55:01 by mtellami          #+#    #+#             */
/*   Updated: 2023/01/19 15:23:39 by mtellami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	quote_analyse(char ***lx, char **buffer, char *input, int *i)
{
	char	quote;

	*buffer = str_concate(*buffer, input[*i]);
	quote = input[(*i)++];
	while (input[*i] && input[*i] != quote)
		*buffer = str_concate(*buffer, input[(*i)++]);
	*buffer = str_concate(*buffer, input[(*i)++]);
	*lx = arr_concate(*lx, *buffer);
}

void	separator_analyse(char ***lx, char **buffer, char *input, int *i)
{
	*buffer = str_concate(*buffer, input[*i]);
	if (input[(*i) + 1] == input[*i])
		*buffer = str_concate(*buffer, input[++(*i)]);
	*lx = arr_concate(*lx, *buffer);
	(*i)++;
}

void	parenthese_analyse(char ***lx, char **buffer, char *input, int *i)
{
	*buffer = str_concate(*buffer, input[(*i)++]);
	*lx = arr_concate(*lx, *buffer);
}

void	words_analyse(char ***lx, char **buffer, char *input, int *i)
{
	while (input[*i] && not_metachar(input[*i]))
		*buffer = str_concate(*buffer, input[(*i)++]);
	*lx = arr_concate(*lx, *buffer);
}

char	**lexer(char *input)
{
	char	**lx;
	char	*buffer;
	int		i;

	lx = NULL;
	buffer = NULL;
	i = 0;
	while (input[i])
	{
		if (input[i] == SPACE)
			space_skiper(input, &i);
		else if (input[i] == SINGLE_QUOTE || input[i] == DOUBLE_QUOTE)
			quote_analyse(&lx, &buffer, input, &i);
		else if (input[i] == PIPE || input[i] == AMPERSAND
			|| input[i] == RIGHT_ARROW || input[i] == LEFT_ARROW)
			separator_analyse(&lx, &buffer, input, &i);
		else if (input[i] == OPEN_PARENTHESE || input[i] == CLOSE_PARENTHESE)
			parenthese_analyse(&lx, &buffer, input, &i);
		else
			words_analyse(&lx, &buffer, input, &i);
		buffer_reset(&buffer);
	}
	return (lx);
}
