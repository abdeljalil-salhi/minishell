/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellami <mtellami@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 11:55:01 by mtellami          #+#    #+#             */
/*   Updated: 2023/01/17 17:53:43 by mtellami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clean_args(char **lx)
{
	char	**buffer;
	int		i;
	int		j;

	buffer = NULL;
	if (!ft_strcmp(lx[0], "(") && !ft_strcmp(lx[ft_tabsize(lx) - 1], ")"))
	{
		buffer = ft_subarr(lx, 1, ft_tabsize(lx) - 2);
		ft_freearr(lx);
		lx = buffer;
	}
	i = 0;
	buffer = NULL;
	while (lx[i])
	{
		if (!ft_strcmp(lx[i], "("))
		{

			j = i;
			while (ft_strcmp(lx[i], ")") && ft_strcmp(lx[i], "&&")
				&& ft_strcmp(lx[i], "|") && ft_strcmp(lx[i], "||"))
				j++;
			if (!ft_strcmp(lx[j], ")"))
			{
				i++;
				while (ft_strcmp(lx[i], ")"))
					buffer = arr_concate(buffer, lx[i++]);
			}
			else
				buffer = arr_concate(buffer, lx[i]);
		}
		else
			buffer = arr_concate(buffer, lx[i]);
		i++;
	}
	ft_freearr(lx);
	lx = buffer;
}

char	**lexer(char *input)
{
	char	**lx;
	char	*buffer;
	char	quote;
	int		i;

	lx = NULL;
	buffer = NULL;
	i = 0;
	while (input[i])
	{
		if (input[i] == SPACE)
			space_skiper(input, &i);
		else if (input[i] == SINGLE_QUOTE || input[i] == DOUBLE_QUOTE)
		{
			buffer = str_concate(buffer, input[i]);
			quote = input[i++];
			while (input[i] && input[i] != quote)
				buffer = str_concate(buffer, input[i++]);
			buffer = str_concate(buffer, input[i++]);
			lx = arr_concate(lx, buffer);
		}
		else if (input[i] == PIPE || input[i] == AMPERSAND
			|| input[i] == RIGHT_ARROW || input[i] == LEFT_ARROW)
		{
			buffer = str_concate(buffer, input[i]);
			if (input[i + 1] == input[i])
				buffer = str_concate(buffer, input[++i]);
			lx = arr_concate(lx, buffer);
			i++;
		}
		else if (input[i] == OPEN_PARENTHESE || input[i] == CLOSE_PARENTHESE)
		{
			buffer = str_concate(buffer, input[i++]);
			lx = arr_concate(lx, buffer);
		}
		else
		{
			while (input[i] && not_metachar(input[i]))
				buffer = str_concate(buffer, input[i++]);
			lx = arr_concate(lx, buffer);
		}
		buffer_reset(&buffer);
	}
	// clean_args(lx);
	return (lx);
}
