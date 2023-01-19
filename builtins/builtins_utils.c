/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellami <mtellami@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 20:01:26 by mtellami          #+#    #+#             */
/*   Updated: 2023/01/18 12:56:15 by mtellami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	value_inquotes(char **env, int i)
{
	int	j;

	j = 0;
	printf("declare -x ");
	while (env[i][j])
	{
		printf("%c", env[i][j]);
		if (env[i][j] == '=')
			break ;
		j++;
	}
	printf("%c%s%c\n", '"', env[i] + j + 1, '"');
}

int	check_var(char *str, char **env)
{
	int	i;
	int	j;

	j = 0;
	while (str[j])
	{
		if (str[j] == '=')
			break ;
		j++;
	}
	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(str, env[i], j))
			if (env[i][j] == '=' || !env[i][j])
				return (i);
		i++;
	}
	return (-1);
}

int	valid_ident(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=')
	{
		if (!((str[i] >= 'a' && str[i] <= 'z')
				|| (str[i] >= 'A' && str[i] <= 'Z')
				|| (str[i] >= '0' && str[i] <= '9')
				|| str[i] == '_'))
		{
			printf("minishell: export: `%s': not a valid identifier\n", str);
			return (1);
		}
		i++;
	}
	if (!i || (str[0] >= '0' && str[0] <= '9'))
	{
		printf("minishell: export: `%s': not a valid identifier\n", str);
		return (1);
	}
	return (0);
}

void	sort_env(char **env)
{
	char	*tmp;
	int		i;
	int		j;

	i = 0;
	while (env[i])
	{
		j = i + 1;
		while (env[j])
		{
			if (ft_strcmp(env[i], env[j]) > 0)
			{
				tmp = env[i];
				env[i] = env[j];
				env[j] = tmp;
			}
			j++;
		}
		i++;
	}
}

void	cd_home(char **env)
{
	char	*path;
	int		i;

	if (!check_home(env))
	{
		printf("minishell: cd: HOME not set\n");
		g_exit_status = EXIT_FAILURE;
	}
	else
	{
		set_oldpwd(env);
		path = home_path(env);
		i = chdir(path);
		if (i)
		{
			printf("minishell: cd: %s: No such file or directory\n", path);
			g_exit_status = EXIT_FAILURE;
			return ;
		}
		set_pwd(env);
	}
}
