/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellami <mtellami@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 20:01:26 by mtellami          #+#    #+#             */
/*   Updated: 2023/02/02 10:23:15 by mtellami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	value_inquotes(int i)
{
	int	j;

	j = 0;
	printf("declare -x ");
	while (g_data.env[i][j])
	{
		printf("%c", g_data.env[i][j]);
		if (g_data.env[i][j] == '=')
			break ;
		j++;
	}
	printf("%c%s%c\n", '"', g_data.env[i] + j + 1, '"');
}

int	check_var(char *str)
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
	while (g_data.env[i])
	{
		if (!ft_strncmp(str, g_data.env[i], j))
			if (g_data.env[i][j] == '=' || !g_data.env[i][j])
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
	if (!i || (str[0] >= '0' && str[0] <= '9') || str[i] == SPACE)
	{
		printf("minishell: export: `%s': not a valid identifier\n", str);
		return (1);
	}
	return (0);
}

void	sort_env(void)
{
	char	*tmp;
	int		i;
	int		j;

	i = 0;
	while (g_data.env[i])
	{
		j = i + 1;
		while (g_data.env[j])
		{
			if (ft_strcmp(g_data.env[i], g_data.env[j]) > 0)
			{
				tmp = g_data.env[i];
				g_data.env[i] = g_data.env[j];
				g_data.env[j] = tmp;
			}
			j++;
		}
		i++;
	}
}

void	cd_home(void)
{
	char	*path;
	int		i;

	if (!check_home())
	{
		printf("minishell: cd: HOME not set\n");
		g_data.exit_status = EXIT_FAILURE;
	}
	else
	{
		set_oldpwd();
		path = home_path();
		i = chdir(path);
		if (i)
		{
			printf("minishell: cd: %s: No such file or directory\n", path);
			g_data.exit_status = EXIT_FAILURE;
			return ;
		}
		set_pwd();
		free(path);
	}
}
