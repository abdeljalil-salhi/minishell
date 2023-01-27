/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   re_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: absalhi <absalhi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 19:56:26 by mtellami          #+#    #+#             */
/*   Updated: 2023/01/27 01:30:35 by absalhi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	edit_var(char *str, char **env, int j)
{
	int	i;

	if (!ft_strchr(str, '='))
		return ;
	i = 0;
	while (env[i])
	{
		if (i == j)
		{
			free(env[i]);
			env[i] = ft_strdup(str);
		}
		i++;
	}
}

char	**add_var(char *str, char **env)
{
	char	**new;
	int		i;

	new = malloc(sizeof(char *) * (ft_tabsize(env) + 2));
	i = 0;
	while (env[i])
	{
		new[i] = ft_strdup(env[i]);
		free(env[i]);
		i++;
	}
	free(env);
	new[i++] = ft_strdup(str);
	new[i] = NULL;
	return (new);
}

void	export_var(char **args, char **env)
{
	int	i;
	int	j;

	i = 1;
	while (args[i])
	{
		if (!valid_ident(args[1]))
		{
			j = check_var(args[i], env);
			if (j == -1)
				env = add_var(args[i], env);
			else
				edit_var(args[i], env, j);
		}
		else
			g_data.exit_status = EXIT_FAILURE;
		i++;
	}
}

void	export_declare(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (!ft_strchr(env[i], '='))
			printf("declare -x %s\n", env[i]);
		else
			value_inquotes(env, i);
		i++;
	}
}

void	re_export(char **args, char **env)
{
	if (args[1])
	{
		export_var(args, env);
		sort_env(env);
	}
	else
		export_declare(env);
}
