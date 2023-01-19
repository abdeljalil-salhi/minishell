/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtellami <mtellami@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 15:13:16 by mtellami          #+#    #+#             */
/*   Updated: 2023/01/19 13:30:00 by mtellami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clear_list(t_data *data)
{
	t_proc	*pc_tmp;
	t_redir	*rd_tmp;

	while (data->head)
	{
		pc_tmp = data->head;
		while (pc_tmp->head)
		{
			rd_tmp = pc_tmp->head;
			pc_tmp->head = pc_tmp->head->next;
			free(rd_tmp);
			rd_tmp = NULL;
		}
		data->head = data->head->next;
		free(pc_tmp);
		pc_tmp = NULL;
	}
}

void	clear(t_data *data)
{
	t_proc	*tmp1;
	t_redir	*tmp2;

	tmp1 = data->head;
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
	clear_list(data);
}
