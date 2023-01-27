/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_rd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: absalhi <absalhi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 16:23:05 by mtellami          #+#    #+#             */
/*   Updated: 2023/01/26 22:50:19 by absalhi          ###   ########.fr       */
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

int	is_arrow(char *str)
{
	if (!ft_strcmp(str, ">"))
		return (OUTPUT);
	else if (!ft_strcmp(str, ">>"))
		return (APPEND);
	else if (!ft_strcmp(str, "<"))
		return (INPUT);
	else if (!ft_strcmp(str, "<<"))
		return (APPEND);
	return (-1);
}

int	check_redir(char **args)
{
	int	i;

	i = 0;
	while (args[i])
	{
		if (is_arrow(args[i]) != -1)
			return (1);
		i++;
	}
	return (0);
}

void	fill_rd(t_proc *tmp, char ***buffer)
{
	t_redir	*node;
	int		i;

	i = 0;
	while (tmp->args[i])
	{
		if (is_arrow(tmp->args[i]) != -1)
		{
			node = rd_new_node(tmp->args[i + 1],
					is_arrow(tmp->args[i]));
			rd_addback(&tmp->head, node);
			i++;
		}
		else
			*buffer = arr_concate(*buffer, tmp->args[i]);
		i++;
	}
}

void	init_rd(void)
{
	t_proc	*tmp;
	char	**buffer;

	tmp = g_data.head;
	while (tmp)
	{
		buffer = NULL;
		if (check_redir(tmp->args))
		{
			fill_rd(tmp, &buffer);
			ft_freearr(tmp->args);
			tmp->args = buffer;
		}
		else
			tmp->head = NULL;
		tmp = tmp->next;
	}
}
