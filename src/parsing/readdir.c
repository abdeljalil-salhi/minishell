/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readdir.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellami <mtellami@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 06:33:55 by mtellami          #+#    #+#             */
/*   Updated: 2023/01/30 07:24:40 by mtellami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

DIR	*open_dir(char *str)
{
	DIR		*dr;
	char	*path;

	if (ft_strrchr(str, '/'))
		path = ft_substr(str, 0, ft_strlen(str)
				- ft_strlen(ft_strrchr(str, '/')));
	else
		path = ft_strdup(".");
	dr = opendir(path);
	if (!dr)
	{
		free(path);
		return (NULL);
	}
	free(path);
	return (dr);
}

char	**get_dir_files(char *str)
{
	struct dirent	*de;
	DIR				*dr;
	int				i;
	char			**buffer;

	dr = open_dir(str);
	if (!dr)
		return (NULL);
	i = 0;
	buffer = NULL;
	while (1)
	{
		de = readdir(dr);
		if (!de)
			break ;
		if (i > 1)
			buffer = arr_concate(buffer, de->d_name);
		i++;
	}
	closedir(dr);
	return (buffer);
}
