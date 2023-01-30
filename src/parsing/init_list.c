/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellami <mtellami@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 16:21:52 by mtellami          #+#    #+#             */
/*   Updated: 2023/01/30 11:51:21 by mtellami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_separator(char **lx, int i)
{
	int	sep;

	sep = -1;
	if (!lx[i])
		sep = LAST_CMD;
	else if (!ft_strcmp(lx[i], "&&"))
		sep = AND_TOKEN;
	else if (!ft_strcmp(lx[i], "||"))
		sep = OR_TOKEN;
	else if (!ft_strcmp(lx[i], "|"))
		sep = PIPE_TOKEN;
	else
	{
		while (lx[i] && !ft_strcmp(lx[i], ")"))
			i++;
		sep = get_separator(lx, i);
	}
	return (sep);
}

void	level_track(char **lx, int *i, int *lvl, int p)
{
	if (!p)
	{
		while (lx[*i] && !ft_strcmp(lx[*i], "("))
		{
			(*lvl)++;
			(*i)++;
		}
	}
	else
	{
		while (lx[*i] && !ft_strcmp(lx[*i], ")"))
		{
			(*lvl)--;
			(*i)++;
		}
	}
}

void	init_list(char **lx)
{
	t_proc	*node;
	char	**buffer;
	int		lvl;
	int		i;

	lvl = 0;
	i = 0;
	g_data.head = NULL;
	while (lx[i])
	{
		level_track(lx, &i, &lvl, 0);
		buffer = NULL;
		while (lx[i] && (ft_strcmp(lx[i], ")") && ft_strcmp(lx[i], "&&")
				&& ft_strcmp(lx[i], "|") && ft_strcmp(lx[i], "||")))
			buffer = arr_concate(buffer, lx[i++]);
		node = pc_new_node(buffer, get_separator(lx, i), lvl);
		pc_addback(&g_data.head, node);
		level_track(lx, &i, &lvl, 1);
		if (lx[i])
			i++;
	}
}
