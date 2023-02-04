/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   re_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellami <mtellami@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 19:56:55 by mtellami          #+#    #+#             */
/*   Updated: 2023/02/04 13:01:07 by mtellami         ###   ########.fr       */
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
	ft_dprintf(STDERR_FILENO, "exit\n");
	if (args[1])
	{
		if (not_num(args[1]))
		{
			ft_dprintf(STDERR_FILENO, ERR_NUMERIC_ARG, args[1]);
			g_data.exit_status = 255;
			exit(g_data.exit_status);
		}
		else if (args[2])
		{
			ft_dprintf(STDERR_FILENO, ERR_TOO_MANY_ARGS);
			g_data.exit_status = 1;
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
