/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   re_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: absalhi <absalhi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 19:57:54 by mtellami          #+#    #+#             */
/*   Updated: 2023/02/05 01:10:49 by absalhi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_oldpwd(void)
{
	char	*cwd;
	int		i;

	cwd = getcwd(NULL, 0);
	if (!cwd)
		return ;
	i = 0;
	while (g_data.env[i])
	{
		if (!ft_strncmp("OLDPWD", g_data.env[i], 6) && g_data.env[i][6] == '=')
		{
			free(g_data.env[i]);
			g_data.env[i] = ft_strcjoin("OLDPWD", '=', cwd);
		}
		i++;
	}
	free(cwd);
}

void	set_pwd(void)
{
	char	*cwd;
	int		i;

	cwd = getcwd(NULL, 0);
	i = 0;
	while (g_data.env[i])
	{
		if (!ft_strncmp("PWD", g_data.env[i], 3) && g_data.env[i][3] == '=')
		{
			free(g_data.env[i]);
			g_data.env[i] = ft_strcjoin("PWD", '=', cwd);
		}
		i++;
	}
	free(cwd);
}

int	check_home(void)
{
	int	i;

	i = 0;
	while (g_data.env[i])
	{
		if (!ft_strncmp("HOME", g_data.env[i], 4))
			if (g_data.env[i][4] == '=' || !g_data.env[i][4])
				return (1);
		i++;
	}
	return (0);
}

void	re_cd(char **args)
{
	char	*cwd;
	int		i;

	cwd = getcwd(NULL, 0);
	if (!args[1])
		cd_home();
	else if (!ft_strcmp(args[1], "-"))
		cd_oldpwd();
	else if (ft_strcmp(args[1], "."))
	{
		set_oldpwd();
		i = chdir(args[1]);
		if (i == -1)
		{
			ft_dprintf(2, CUSTOM_2, "cd", args[1], strerror(errno));
			g_data.exit_status = 1;
			free(cwd);
			return ;
		}
		set_pwd();
	}
	else if (!cwd)
		ft_dprintf(2, "cd: error retrieving current directory: getcwd:\
		cannot access parent directories: No such file or directory\n");
	free(cwd);
}
