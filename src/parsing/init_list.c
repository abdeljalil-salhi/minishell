/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellami <mtellami@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 16:21:52 by mtellami          #+#    #+#             */
/*   Updated: 2023/01/19 16:44:22 by mtellami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	init_list(char **lx, t_data *data)
{
	t_proc	*node;
	char	**buffer;
	int		lvl;
	int		i;

	lvl = 0;
	i = 0;
	data->head = NULL;
	while (lx[i])
	{
		level_track(lx, &i, &lvl, 0);
		buffer = NULL;
		while (lx[i] && (ft_strcmp(lx[i], ")") && ft_strcmp(lx[i], "&&")
				&& ft_strcmp(lx[i], "|") && ft_strcmp(lx[i], "||")))
			buffer = arr_concate(buffer, lx[i++]);
		node = pc_new_node(buffer, get_separator(lx, i), lvl);
		pc_addback(&data->head, node);
		level_track(lx, &i, &lvl, 1);
		if (lx[i])
			i++;
	}
}
