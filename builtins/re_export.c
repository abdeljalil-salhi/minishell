/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   re_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellami <mtellami@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 19:56:26 by mtellami          #+#    #+#             */
/*   Updated: 2023/02/02 10:22:46 by mtellami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	edit_var(char *str, int j)
{
	int	i;

	if (!ft_strchr(str, '='))
		return ;
	i = 0;
	while (g_data.env[i])
	{
		if (i == j)
		{
			free(g_data.env[i]);
			g_data.env[i] = ft_strdup(str);
		}
		i++;
	}
}

char	**add_var(char *str)
{
	char	**new;
	int		i;

	new = malloc(sizeof(char *) * (ft_tabsize(g_data.env) + 2));
	i = 0;
	while (g_data.env[i])
	{
		new[i] = ft_strdup(g_data.env[i]);
		free(g_data.env[i]);
		i++;
	}
	free(g_data.env);
	new[i++] = ft_strdup(str);
	new[i] = NULL;
	return (new);
}

void	export_var(char **args)
{
	int	i;
	int	j;

	i = 1;
	while (args[i])
	{
		if (!valid_ident(args[i]))
		{
			j = check_var(args[i]);
			if (j == -1)
				g_data.env = add_var(args[i]);
			else
				edit_var(args[i], j);
		}
		else
			g_data.exit_status = EXIT_FAILURE;
		i++;
	}
}

void	export_declare(void)
{
	int	i;

	i = 0;
	while (g_data.env[i])
	{
		if (!ft_strchr(g_data.env[i], '='))
			printf("declare -x %s\n", g_data.env[i]);
		else
			value_inquotes(i);
		i++;
	}
}

void	re_export(char **args)
{
	if (args[1])
	{
		export_var(args);
		sort_env();
	}
	else
		export_declare();
}
