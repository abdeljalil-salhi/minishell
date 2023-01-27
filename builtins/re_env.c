/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   re_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: absalhi <absalhi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 19:57:13 by mtellami          #+#    #+#             */
/*   Updated: 2023/01/27 04:08:39 by absalhi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	re_env(char **args)
{
	int	i;

	(void) args;
	i = -1;
	while (g_data.env[++i])
		if (ft_strchr(g_data.env[i], '='))
			printf("%s\n", g_data.env[i]);
}
