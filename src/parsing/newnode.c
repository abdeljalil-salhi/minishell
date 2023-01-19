/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   newnode.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellami <mtellami@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 09:41:41 by mtellami          #+#    #+#             */
/*   Updated: 2023/01/18 19:25:28 by mtellami         ###   ########.fr       */
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
	new->level = lvl;
	new->head = NULL;
	new->previous = NULL;
	new->next = NULL;
	return (new);
}