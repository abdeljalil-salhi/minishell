/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   re_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellami <mtellami@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 19:57:54 by mtellami          #+#    #+#             */
/*   Updated: 2023/01/18 12:20:28 by mtellami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_oldpwd(char **env)
{
	char	*cwd;
	int		i;

	cwd = getcwd(NULL, 0);
	i = 0;
	while (env[i])
	{
		if (!ft_strncmp("OLDPWD", env[i], 6) && env[i][6] == '=')
		{
			free(env[i]);
			env[i] = ft_strcjoin("OLDPWD", '=', cwd);
		}
		i++;
	}
}

void	set_pwd(char **env)
{
	char	*cwd;
	int		i;

	cwd = getcwd(NULL, 0);
	i = 0;
	while (env[i])
	{
		if (!ft_strncmp("PWD", env[i], 3) && env[i][3] == '=')
		{
			free(env[i]);
			env[i] = ft_strcjoin("PWD", '=', cwd);
		}
		i++;
	}
}

int	check_home(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (!ft_strncmp("HOME", env[i], 4))
			if (env[i][4] == '=' || !env[i][4])
				return (1);
		i++;
	}
	return (0);
}

char	*home_path(char **env)
{
	char	*path;
	int		i;

	i = 0;
	while (env[i])
	{
		if (!ft_strncmp("HOME", env[i], 4))
		{
			path = ft_strdup(env[i] + 5);
			return (path);
		}
		i++;
	}
	return (NULL);
}

void	re_cd(char **args, char **env)
{
	int	i;

	if (!args[1])
		cd_home(env);
	else if (ft_strcmp(args[1], "."))
	{
		set_oldpwd(env);
		i = chdir(args[1]);
		if (i == -1)
		{
			printf("minishell: cd: %s: No such file or directory\n", args[1]);
			g_exit_status = 1;
			return ;
		}
		set_pwd(env);
	}
}
