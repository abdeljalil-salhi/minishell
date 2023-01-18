/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_values.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellami <mtellami@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 17:48:07 by mtellami          #+#    #+#             */
/*   Updated: 2023/01/18 17:48:09 by mtellami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

 #include "minishell.h"

char	*get_env_values(char *str, char **env)
{
	char	*ptr;
	int		i;

	i = 0;
	while (env[i])
	{
		ptr = ft_strstr(env[i], str);
		if (ptr)
		{
			if (*(ptr + ft_strlen(str)) == '=' && str[0] == env[i][0])
			{
				ptr = ft_strdup(env[i] + (ft_strlen(str) + 1));
				free(str);
				return (ptr);
			}
		}
		i++;
	}
	if (!ft_strcmp(str, "?"))
		ptr = ft_itoa(g_exit_status);
	else
		ptr = ft_strdup("");
	free(str);
	return (ptr);
}
