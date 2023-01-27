/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   re_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: absalhi <absalhi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 19:57:13 by mtellami          #+#    #+#             */
/*   Updated: 2023/01/28 00:14:12 by absalhi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	re_env(char **args)
{
	int	i;

	(void) args;
	i = -1;
	while (g_data.env[++i])
	{
		if (!ft_strncmp(g_data.env[i], "PATH=", 5))
		{
			i = -1;
			break ;
		}
	}
	if (i != -1)
	{
		printf("minishell: env: No such file or directory\n");
		g_data.exit_status = 127;
		return ;
	}
	while (g_data.env[++i])
		if (ft_strchr(g_data.env[i], '='))
			printf("%s\n", g_data.env[i]);
}
