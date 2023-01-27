/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: absalhi <absalhi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 00:19:59 by absalhi           #+#    #+#             */
/*   Updated: 2023/01/27 02:05:13 by absalhi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_builtins(void)
{
	g_data.builtins[0].name = "echo";
	g_data.builtins[0].func = &re_echo;
	g_data.builtins[1].name = "cd";
	g_data.builtins[1].func = &re_cd;
	g_data.builtins[2].name = "pwd";
	g_data.builtins[2].func = &re_pwd;
	g_data.builtins[3].name = "export";
	g_data.builtins[3].func = &re_export;
	g_data.builtins[4].name = "unset";
	g_data.builtins[4].func = &re_unset;
	g_data.builtins[5].name = "env";
	g_data.builtins[5].func = &re_env;
	g_data.builtins[6].name = "exit";
	g_data.builtins[6].func = &re_exit;
}

int	is_builtin(char *cmd)
{
	return (ft_strcmp(cmd, "echo") == 0 || ft_strcmp(cmd, "cd") == 0
		|| ft_strcmp(cmd, "pwd") == 0 || ft_strcmp(cmd, "export") == 0
		|| ft_strcmp(cmd, "unset") == 0 || ft_strcmp(cmd, "env") == 0
		|| ft_strcmp(cmd, "exit") == 0);
}

int	exec_builtin(char *cmd, char **args)
{
	int	i;

	i = -1;
	while (++i < 7)
	{
		if (ft_strcmp(cmd, g_data.builtins[i].name) == 0)
		{
			g_data.builtins[i].func(args, g_data.env);
			return (0);
		}
	}
	return (1);
}
