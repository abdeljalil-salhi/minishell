/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   re_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellami <mtellami@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 19:56:55 by mtellami          #+#    #+#             */
/*   Updated: 2023/02/03 08:43:40 by mtellami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cd_oldpwd(void)
{
	char	*path;
	int		i;
	
	i = 0;
	path = NULL;
	while (g_data.env[i])
	{
		if (!ft_strncmp(g_data.env[i], "OLDPWD=", 7))
		{
			path = ft_strdup(g_data.env[i] + 7);
			break ;
		}
		i++;
	}
	if (!path)
	{
		ft_dprintf(STDERR_FILENO, ERR_UNSET, "OLDPWD");
		g_data.exit_status = EXIT_FAILURE;
	}
	else
	{
		set_oldpwd();
		i = chdir(path);
		if (i)
		{
			ft_dprintf(STDERR_FILENO, ERR_NO_SUCH_FILE_2, "cd", path);
			g_data.exit_status = EXIT_FAILURE;
			return ;
		}
		set_pwd();
		free(path);
	}
}

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
