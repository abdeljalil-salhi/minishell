/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   re_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: absalhi <absalhi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 19:56:55 by mtellami          #+#    #+#             */
/*   Updated: 2023/01/27 04:09:04 by absalhi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	not_num(char *str)
{
	if (!(*str))
		return (1);
	if (*str == '-' || *str == '+')
		str++;
	if (!(*str))
		return (1);
	while (*str)
	{
		if (*str < '0' || *str > '9')
			return (1);
		str++;
	}
	return (0);
}

void	re_exit(char **args)
{
	printf("exit\n");
	if (args[1])
	{
		if (not_num(args[1]))
		{
			printf("minishell: exit: %s: numeric argument required\n", args[1]);
			g_data.exit_status = EXIT_FAILURE;
			exit(EXIT_FAILURE);
		}
		else if (args[2])
		{
			printf("minishell: exit: too many arguments\n");
			return ;
		}
		else
		{
			g_data.exit_status = ft_atoi(args[1]);
			exit(g_data.exit_status);
		}
	}
	exit(EXIT_SUCCESS);
}
