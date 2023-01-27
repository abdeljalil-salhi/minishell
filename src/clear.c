/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: absalhi <absalhi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 15:13:16 by mtellami          #+#    #+#             */
/*   Updated: 2023/01/26 22:47:44 by absalhi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clear_list(void)
{
	t_proc	*pc_tmp;
	t_redir	*rd_tmp;

	while (g_data.head)
	{
		pc_tmp = g_data.head;
		while (pc_tmp->head)
		{
			rd_tmp = pc_tmp->head;
			pc_tmp->head = pc_tmp->head->next;
			free(rd_tmp);
			rd_tmp = NULL;
		}
		g_data.head = g_data.head->next;
		free(pc_tmp);
		pc_tmp = NULL;
	}
}

void	clear(void)
{
	t_proc	*tmp1;
	t_redir	*tmp2;

	tmp1 = g_data.head;
	while (tmp1)
	{
		tmp2 = tmp1->head;
		while (tmp2)
		{
			free(tmp2->file);
			tmp2 = tmp2->next;
		}
		free(tmp1->cmd);
		if (tmp1->args)
			ft_freearr(tmp1->args);
		tmp1 = tmp1->next;
	}
	clear_list();
}
