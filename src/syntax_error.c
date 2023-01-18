/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellami <mtellami@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 11:54:11 by mtellami          #+#    #+#             */
/*   Updated: 2023/01/18 08:37:18 by mtellami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	separator_check(char **lx, int i)
{
	if (!ft_strcmp(lx[i], "||") || !ft_strcmp(lx[i], "|") || !ft_strcmp(lx[i], "&&"))
	{
		if (!lx[i + 1] || !ft_strcmp(lx[i + 1], "||") || !ft_strcmp(lx[i + 1], "|")
			|| !ft_strcmp(lx[i + 1], "&&"))
		{
			if (!lx[i + 1])
				printf("minishell: syntax error near unexpected token `%s'\n", lx[i]);
			else
				printf("minishell: syntax error near unexpected token `%s'\n", lx[i + 1]);
			return (1);
		}
	}
	return (0);
}

int	redirection_check(char **lx, int i)
{
	if (!ft_strcmp(lx[i], ">>") || !ft_strcmp(lx[i], "<<")
		|| !ft_strcmp(lx[i], ">") || !ft_strcmp(lx[i], "<"))
	{
		if (!lx[i + 1])
		{
			printf("minishell: syntax error near unexpected token `newline'\n");
			return (1);
		}
		else if (!ft_strcmp(lx[i + 1], ">>") || !ft_strcmp(lx[i + 1], "<<")
			|| !ft_strcmp(lx[i + 1], ">") || !ft_strcmp(lx[i + 1], "<")
			|| !ft_strcmp(lx[i + 1], "|") || !ft_strcmp(lx[i + 1], "||")
			|| !ft_strcmp(lx[i + 1], "&&"))
		{
			printf("minishell: syntax error near unexpected token `%s'\n", lx[i + 1]);
			return (1);
		}
	}
	return (0);
}

int	parentheses_check(char **lx, int i, int *x, int *y)
{
	if (!ft_strcmp(lx[i], "("))
	{
		(*x)++;
		if (i && ft_strcmp(lx[i - 1], "&&") && ft_strcmp(lx[i - 1], "||")
			&& ft_strcmp(lx[i - 1], "|") && ft_strcmp(lx[i - 1], "("))
		{
			printf("minishell: syntax error near unexpected token `%s'\n", lx[i]);
			return (1);
		}
		if (!ft_strcmp(lx[i + 1], ")") || !ft_strcmp(lx[i + 1], "&&")
			|| !ft_strcmp(lx[i + 1], "||") || !ft_strcmp(lx[i + 1], "||"))
		{
			printf("minishell: syntax error near unexpected token `%s'\n", lx[i + 1]);
			return (1);
		}
	}
	else if (!ft_strcmp(lx[i], ")"))
	{
		(*y)++;
		if (lx[i + 1] && ft_strcmp(lx[i + 1], "&&") && ft_strcmp(lx[i + 1], "||")
			&& ft_strcmp(lx[i + 1], "|") && ft_strcmp(lx[i + 1], ")"))
		{
			printf("minishell: syntax error near unexpected token `%s'\n", lx[i + 1]);
			return (1);
		}
	}
	if (!lx[i + 1])
	{
		if (*x > *y)
		{
			printf("minishell: syntax error near unexpected tokeen `('\n");
			return (1);
		}
		else if (*x < *y)
		{
			printf("minishell: syntax error near unexpected tokeen `)'\n");
			return (1);
		}
	}
	return (0);
}

int	quote_check(char *str)
{
	if (str[0] == SINGLE_QUOTE || str[0] == DOUBLE_QUOTE)
	{
		if (str[ft_strlen(str) - 1] != str[0] || ft_strlen(str) == 1)
		{
			printf("minishell: syntax error near unclosed quotation mark\n");		
			return (1);
		}
	}
	return (0);
}

int	syntax_error(char **lx)
{
	int	i;
	int	x;
	int y;

	i = 0;
	x = 0;
	y = 0;
	while (lx[i])
	{
		if (quote_check(lx[i]))
			return (1);
		else if (separator_check(lx, i))
			return (1);
		else if (!ft_strcmp(lx[i], "&") || !ft_strcmp(lx[0], "&&")
			|| !ft_strcmp(lx[0], "||") || !ft_strcmp(lx[0], "|"))
		{
			printf("minishell: syntax error near unexpected token `%s'\n", lx[i]);
			return (1);
		}
		else if (redirection_check(lx, i))
			return (1);
		else if (parentheses_check(lx, i, &x, &y))
			return (1);
		i++;
	}
	return (0);
}
