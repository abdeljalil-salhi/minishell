/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_addback.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellami <mtellami@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 16:56:24 by mtellami          #+#    #+#             */
/*   Updated: 2023/01/18 19:25:25 by mtellami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	rd_addback(t_redir **head, t_redir *new)
{
	t_redir	*tmp;

	tmp = *head;
	if (!head || !new)
		return ;
	if (*head)
	{
		tmp = rd_last_node(tmp);
		tmp->next = new;
		new->previous = tmp;
	}
	else
		*head = new;
}

void	pc_addback(t_proc **head, t_proc *new)
{
	t_proc	*tmp;

	tmp = *head;
	if (!head || !new)
		return ;
	if (*head)
	{
		tmp = pc_last_node(tmp);
		tmp->next = new;
		new->previous = tmp;
	}
	else
		*head = new;
}
