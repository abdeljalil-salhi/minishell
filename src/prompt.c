/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: absalhi <absalhi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 08:48:57 by mtellami          #+#    #+#             */
/*   Updated: 2023/01/30 13:19:35 by absalhi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*prompt(void)
{
	char	*path;
	char	*folder;
	char	*user;
	char	*color;

	path = getcwd(NULL, 0);
	user = ft_strdup("$USER");
	user = expand(user);
	if (g_data.exit_status == 0)
		color = GREEN;
	else
		color = RED;
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
