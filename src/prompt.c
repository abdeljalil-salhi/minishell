/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellami <mtellami@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 08:48:57 by mtellami          #+#    #+#             */
/*   Updated: 2023/01/30 08:49:32 by mtellami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*prompt(void)
{
	char	*path;
	char	*folder;
	char	*user;

	path = getcwd(NULL, 0);
	user = ft_strdup("$USER");
	user = expand(user);
	if (ft_strlen(path) != ft_strlen(ft_strrchr(path, '/')))
	{
		if (!ft_strcmp(user, ft_strrchr(path, '/') + 1))
			folder = ft_strjoin(GREEN, "~");
		else
			folder = ft_strjoin(GREEN, ft_strrchr(path, '/') + 1);
	}
	else
		folder = ft_strjoin(GREEN, ft_strrchr(path, '/'));
	free(path);
	path = ft_strjoin(folder, RESET);
	free(folder);
	free(user);
	return (path);
}
