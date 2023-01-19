/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   re_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellami <mtellami@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 19:54:16 by mtellami          #+#    #+#             */
/*   Updated: 2023/01/18 12:59:17 by mtellami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	validate(char *str)
{
	int	i;

	i = 0;
	while (str[i] && ((str[i] >= 'a' && str[i] <= 'z')
			|| (str[i] >= 'A' && str[i] <= 'Z')
			|| (str[i] >= '0' && str[i] <= '9')
			|| str[i] == '_'))
		i++;
	if (i != ft_strlen(str))
		return (0);
	return (1);
}

void	delete_var(char **new, char **env, int x)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (env[i])
	{
		if (i != x)
			new[j++] = ft_strdup(env[i]);
		i++;
	}
	new[j] = NULL;
	ft_freearr(env);
}

int	get_var(char *str, char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(str, env[i], ft_strlen(str)))
			if (env[i][ft_strlen(str)] == '=' || !env[i][ft_strlen(str)])
				return (i);
		i++;
	}
	return (-1);
}

char	**update_env(char *str, char **env)
{
	char	**new;
	int		i;

	i = get_var(str, env);
	if (i == -1)
		return (env);
	new = malloc(sizeof(char *) * ft_tabsize(env));
	if (!new)
		exit(EXIT_FAILURE);
	delete_var(new, env, i);
	return (new);
}

void	re_unset(char **args, char **env)
{
	int	i;

	i = 1;
	while (args[i])
	{
		if (!validate(args[i]))
		{
			printf("bash: unset: `%s': not a valid identifier\n", args[i]);
			g_exit_status = EXIT_FAILURE;
		}
		else
			env = update_env(args[i], env);
		i++;
	}
}
