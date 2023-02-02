/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   absolute_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellami <mtellami@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 15:17:16 by mtellami          #+#    #+#             */
/*   Updated: 2023/02/02 13:04:39 by mtellami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**get_secure_paths(char **env)
{
	char	**tree;
	int		i;

	i = 0;
	while (env[i])
	{
		if (ft_strstr(env[i], "PATH"))
		{
			tree = ft_split(env[i] + 5, ':');
			return (tree);
		}
		i++;
	}
	return (NULL);
}

int	check_builtins(char *cmd)
{
	if (!ft_strcmp(cmd, "echo") || !ft_strcmp(cmd, "cd")
		|| !ft_strcmp(cmd, "pwd") || !ft_strcmp(cmd, "export")
		|| !ft_strcmp(cmd, "unset") || !ft_strcmp(cmd, "env")
		|| !ft_strcmp(cmd, "exit"))
		return (0);
	return (1);
}

int	check_path(char **tree, char **path, char *cmd)
{
	int	i;

	i = 0;
	if (!(*cmd))
		return (0);
	while (tree[i])
	{
		*path = ft_strcjoin(tree[i], '/', cmd);
		if (!access(*path, F_OK))
		{
			ft_freearr(tree);
			return (1);
		}
		free(*path);
		i++;
	}
	ft_freearr(tree);
	return (0);
}

char	*absolute_path(char *cmd)
{
	char	*path;
	char	**tree;

	if (!cmd)
		return (NULL);
	if (!check_builtins(cmd))
	{
		path = ft_strdup(cmd);
		return (path);
	}
	tree = get_secure_paths(g_data.env);
	if (!tree)
		return (NULL);
	path = NULL;
	if (check_path(tree, &path, cmd))
		return (path);
	if (!access(cmd, F_OK))
	{
		path = ft_strdup(cmd);
		return (path);
	}
	return (NULL);
}
