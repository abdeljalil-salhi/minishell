/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   supervisor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: absalhi <absalhi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 21:38:16 by absalhi           #+#    #+#             */
/*   Updated: 2023/01/27 02:55:23 by absalhi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	supervisor(void)
{
	t_proc	*current;

	current = g_data.head;
	while (current)
	{
		if (DEBUG)
		{
			printf("   ~ current->cmd = %s\n", current->cmd);
			printf("   ~ current->separator = %d\n", current->separator);
			printf("   ~ current->level = %d\n", current->level);
			printf("   ~ current->next = %p\n", current->next);
		}
		if (current->separator == LAST_CMD)
			g_data.exit_status = executor(current);
		current = current->next;
	}
}
