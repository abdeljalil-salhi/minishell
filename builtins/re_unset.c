/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   re_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: absalhi <absalhi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 19:54:16 by mtellami          #+#    #+#             */
/*   Updated: 2023/02/03 04:20:55 by absalhi          ###   ########.fr       */
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

void	delete_var(char **new, int x)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (g_data.env[i])
	{
		if (i != x)
			new[j++] = ft_strdup(g_data.env[i]);
		i++;
	}
	new[j] = NULL;
	ft_freearr(g_data.env);
}

int	get_var(char *str)
{
	int	i;

	i = 0;
	while (g_data.env[i])
	{
		if (!ft_strncmp(str, g_data.env[i], ft_strlen(str)))
			if (g_data.env[i][ft_strlen(str)] == '='
				|| !g_data.env[i][ft_strlen(str)])
				return (i);
		i++;
	}
	return (-1);
}

char	**update_env(char *str)
{
	char	**new;
	int		i;

	i = get_var(str);
	if (i == -1)
		return (g_data.env);
	new = malloc(sizeof(char *) * ft_tabsize(g_data.env));
	if (!new)
		exit(EXIT_FAILURE);
	delete_var(new, i);
	return (new);
}

void	re_unset(char **args)
{
	int	i;

	i = 1;
	while (args[i])
	{
		if (!validate(args[i]))
		{
			ft_dprintf(STDERR_FILENO, ERR_INVALID_IDENT, "unset", args[i]);
			g_data.exit_status = EXIT_FAILURE;
		}
		else
			g_data.env = update_env(args[i]);
		i++;
	}
}
