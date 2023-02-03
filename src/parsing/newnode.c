/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   newnode.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: absalhi <absalhi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 09:41:41 by mtellami          #+#    #+#             */
/*   Updated: 2023/02/03 03:54:58 by absalhi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_redir	*rd_new_node(char *file, int type)
{
	t_redir	*new;

	new = malloc(sizeof(t_redir));
	if (!new)
		return (NULL);
	new->file = ft_strdup(file);
	new->fd = -1;
	new->type = type;
	new->next = NULL;
	new->previous = NULL;
	return (new);
}

t_proc	*pc_new_node(char **args, int sep, int lvl)
{
	t_proc	*new;

	new = malloc(sizeof(t_proc));
	if (!new)
		return (NULL);
	new->cmd = NULL;
	new->args = args;
	new->separator = sep;
	new->error = 0;
	new->level = lvl;
	new->head = NULL;
	new->previous = NULL;
	new->next = NULL;
	return (new);
}
