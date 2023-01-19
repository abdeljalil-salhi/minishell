/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   re_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellami <mtellami@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 19:57:32 by mtellami          #+#    #+#             */
/*   Updated: 2023/01/18 11:56:56 by mtellami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_args(char **args, int n)
{
	int	i;

	i = 0;
	while (args[i])
	{
		printf("%s", args[i++]);
		if (args[i])
			printf(" ");
	}
	if (!i || n)
		printf("\n");
}

int	only_n(char *str)
{
	if (!(*str))
		return (1);
	while (*str)
	{
		if (*str != 'n')
			return (1);
		str++;
	}
	return (0);
}

void	n_option(char **args)
{
	if (!only_n(args[1] + 1))
		print_args(args + 2, 0);
	else
		print_args(args + 1, 1);
}

void	re_echo(char **args)
{
	if (!args[1])
		printf("\n");
	else if (args[1][0] == '-')
		n_option(args);
	else
		print_args(args + 1, 1);
}
