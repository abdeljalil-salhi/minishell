/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   re_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellami <mtellami@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 19:56:55 by mtellami          #+#    #+#             */
/*   Updated: 2023/01/10 20:00:12 by mtellami         ###   ########.fr       */
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

void	re_exit(char **arg)
{
	printf("exit\n");
	if (arg[1])
	{
		if (not_num(arg[1]))
		{
			printf("minishell: exit: %s: numeric argument required\n", arg[1]);
			g_exit_status = EXIT_FAILURE;
			exit(EXIT_FAILURE);
		}
		else if (arg[2])
		{
			printf("minishell: exit: too many arguments\n");
			return ;
		}
		else
		{
			g_exit_status = ft_atoi(arg[1]);
			exit(g_exit_status);
		}
	}
	exit(EXIT_SUCCESS);
}
