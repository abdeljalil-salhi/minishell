/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parentheses_check.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellami <mtellami@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 15:28:50 by mtellami          #+#    #+#             */
/*   Updated: 2023/01/21 07:36:35 by mtellami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	open_parenth_check(char **lx, int *x, int i)
{
	(*x)++;
	if (i && ft_strcmp(lx[i - 1], "&&") && ft_strcmp(lx[i - 1], "||")
		&& ft_strcmp(lx[i - 1], "|") && ft_strcmp(lx[i - 1], "("))
	{
		printf("minishell: syntax error near unexpected token `%s'\n",
			lx[i]);
		return (1);
	}
	if (lx[i + 1] && (!ft_strcmp(lx[i + 1], ")") || !ft_strcmp(lx[i + 1], "&&")
			|| !ft_strcmp(lx[i + 1], "||") || !ft_strcmp(lx[i + 1], "||")))
	{
		printf("minishell: syntax error near unexpected token `%s'\n",
			lx[i + 1]);
		return (1);
	}
	return (0);
}

int	close_parenth_check(char **lx, int *y, int i)
{
	(*y)++;
	if (lx[i + 1] && ft_strcmp(lx[i + 1], "&&")
		&& ft_strcmp(lx[i + 1], "||") && ft_strcmp(lx[i + 1], "|")
		&& ft_strcmp(lx[i + 1], ")"))
	{
		printf("minishell: syntax error near unexpected token `%s'\n",
			lx[i + 1]);
		return (1);
	}
	return (0);
}

int	parentheses_check(char **lx, int i, int *x, int *y)
{
	if (!ft_strcmp(lx[i], "("))
	{
		if (open_parenth_check(lx, x, i))
			return (1);
	}
	else if (!ft_strcmp(lx[i], ")"))
	{
		if (close_parenth_check(lx, y, i))
			return (1);
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
