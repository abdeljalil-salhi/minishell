/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellami <mtellami@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 23:12:04 by mtellami          #+#    #+#             */
/*   Updated: 2023/01/30 06:34:18 by mtellami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_wildcard(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == SINGLE_QUOTE || str[i] == DOUBLE_QUOTE)
			return (0);
		else if (str[i] == ASTERISK)
			return (1);
		i++;
	}
	return (0);
}

void	add_filename(char ***buffer, char *str, char *filename)
{
	char	*prx;
	char	*tmp;

	if (ft_strrchr(str, '/'))
	{
		prx = ft_substr(str, 0, ft_strlen(str)
				- ft_strlen(ft_strrchr(str, '/')));
		tmp = ft_strcjoin(prx, '/', filename);
		*buffer = arr_concate(*buffer, tmp);
		free(prx);
		free(tmp);
	}
	else
		*buffer = arr_concate(*buffer, filename);
}

int	searched_file(char *filename, char *str)
{
	char	**arr;
	int		i;

	if (ft_strchr(str, '/'))
		str = ft_strrchr(str, '/') + 1;
	arr = ft_split(str, '*');
	i = -1;
	while (arr[++i])
	{
		if (!ft_strstr(filename, arr[i]))
		{
			ft_freearr(arr);
			return (0);
		}
	}
	ft_freearr(arr);
	return (1);
}

char	**expand_wildcard(char **buffer, char *str)
{
	char	**tree;
	char	**tab;
	int		i;

	if (!buffer)
	{
		buffer = malloc(sizeof(char *));
		*buffer = NULL;
	}
	tab = ft_tabdup(buffer);
	i = 0;
	tree = get_dir_files(str);
	while (tree[i])
	{
		if (searched_file(tree[i], str))
			add_filename(&tab, str, tree[i]);
		i++;
	}
	if (ft_tabsize(buffer) == ft_tabsize(tab))
		tab = arr_concate(tab, str);
	ft_freearr(buffer);
	ft_freearr(tree);
	return (tab);
}

void	wildcard(t_proc *proc)
{
	char	**buffer;
	int		i;

	i = 0;
	buffer = NULL;
	while (proc->args[i])
	{
		if (is_wildcard(proc->args[i]))
			buffer = expand_wildcard(buffer, proc->args[i]);
		else
			buffer = arr_concate(buffer, proc->args[i]);
		i++;
	}
	ft_freearr(proc->args);
	proc->args = buffer;
}
