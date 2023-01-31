/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellami <mtellami@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 08:48:57 by mtellami          #+#    #+#             */
/*   Updated: 2023/01/31 07:13:06 by mtellami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_cwd_env(void)
{
	char	*cwd;
	int		i;

	i = 0;
	while (g_data.env[i])
	{
		if (!ft_strncmp(g_data.env[i], "PWD=", 4))
			cwd = ft_strdup(g_data.env[i] + 4);
		i++;
	}
	return (cwd);
}

char	*prompt(void)
{
	char	*path;
	char	*folder;
	char	*user;
	char	*color;

	path = getcwd(NULL, 0);
	if (!path)
	{
		path = get_cwd_env();
	}
	user = ft_strdup("$USER");
	user = expand(user);
	if (g_data.exit_status == 0)
		color = GREEN_ARROW;
	else
		color = RED_ARROW;
	if (ft_strlen(path) != ft_strlen(ft_strrchr(path, '/')))
	{
		if (!ft_strcmp(user, ft_strrchr(path, '/') + 1))
			folder = ft_strjoin(color, "~");
		else
			folder = ft_strjoin(color, ft_strrchr(path, '/') + 1);
	}
	else
		folder = ft_strjoin(color, ft_strrchr(path, '/'));
	free(path);
	path = ft_strjoin(folder, RESET);
	free(folder);
	free(user);
	return (path);
}
