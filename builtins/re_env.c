/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   re_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: absalhi <absalhi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 19:57:13 by mtellami          #+#    #+#             */
/*   Updated: 2023/01/27 01:55:01 by absalhi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	re_env(char **args, char **env)
{
	int	i;

	(void) args;
	i = -1;
	while (env[++i])
		if (ft_strchr(env[i], '='))
			printf("%s\n", env[i]);
}
