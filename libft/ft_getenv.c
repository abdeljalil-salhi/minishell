/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellami <mtellami@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 14:11:44 by mtellami          #+#    #+#             */
/*   Updated: 2023/02/04 14:19:06 by mtellami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_getenv(char *str)
{
	char	*value;
	int		i;

	i = 0;
	value = NULL;
	while (g_data.env[i])
	{
		if (!ft_strncmp(g_data.env[i], str, ft_strlen(str))
			&& g_data.env[i][ft_strlen(str)] == '=')
		{
			value = ft_strdup(g_data.env[i] + ft_strlen(str) + 1);
			break ;
		}
		i++;
	}
	return (value);
}
